cmake_minimum_required( VERSION 3.30 )

# Control whether kwxFFI is built as static or shared library
# Must be defined before project() for runtime library configuration
option( KWXFFI_BUILD_SHARED "Build kwxFFI as shared library (DLL/SO)" OFF )

string( TIMESTAMP YEAR "%y" ) # e.g., "25"
string( TIMESTAMP DOY "%j" ) # e.g., "192"
string( TIMESTAMP PROJECT_YEAR "%Y" )
math( EXPR BUILD_NUM "${YEAR}%100 * 1000 + ${DOY}" )

set( PROJECT_VERSION_MAJOR 0 )
set( PROJECT_VERSION_MINOR 1 )
set( PROJECT_VERSION_PATCH 0 )
set( PROJECT_VERSION_BUILD ${BUILD_NUM} )
set( PROJECT_VERSION_YEAR ${PROJECT_YEAR} )

project( kwxFFI
    LANGUAGES
    CXX C
    VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_BUILD}
    DESCRIPTION "wxWidgets Foreign Function Interface"
    HOMEPAGE_URL "https://github.com/KeyWorksRW/kwxFFI"
)

# Force release runtime in Debug builds when building shared DLL
# Must be AFTER project() so compiler is detected, but BEFORE any targets are created
if( MSVC AND KWXFFI_BUILD_SHARED )
    # Explicitly set runtime flags for Debug configuration
    set( CMAKE_CXX_FLAGS_DEBUG "/MD /Zi /Ob0 /Od /RTC1" CACHE STRING "C++ Debug with release runtime" FORCE )
    set( CMAKE_C_FLAGS_DEBUG "/MD /Zi /Ob0 /Od /RTC1" CACHE STRING "C Debug with release runtime" FORCE )
    # Also set for Release to ensure consistency
    string( REPLACE "/MT" "/MD" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" )
    string( REPLACE "/MT" "/MD" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" )
    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "C++ Release flags" FORCE )
    set( CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C Release flags" FORCE )
endif()

# ###################### Check for Multi-Config Generator #######################
get_property( isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG )

if( NOT isMultiConfig )
    message( "\nBecause you are using a single target generator, you MUST specify" )
    message( "    a \"--config [Debug|Release]\" option with the cmake --build command\n" )

    set( allowedBuildTypes Debug Release )
    set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${allowedBuildTypes}" )

    if( NOT CMAKE_BUILD_TYPE )
        set( CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE )
    elseif( NOT CMAKE_BUILD_TYPE IN_LIST allowedBuildTypes )
        message( FATAL_ERROR "Unknown build type: ${CMAKE_BUILD_TYPE}" )
    endif()
endif()

# ###################### General Settings #######################
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( CMAKE_CXX_EXTENSIONS OFF )

# ###################### Options #######################
# Only generate compile_commands.json for local development
if( NOT DEFINED ENV{CI} )
    # creates a compile_commands.json file in the build directory, suitable for clangd
    set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
endif()

# Keep BUILD_SHARED_LIBS OFF so wxWidgets dependencies (libwebp) build as static.
# kwxFFI library type is controlled by KWXFFI_BUILD_SHARED option.
set( BUILD_SHARED_LIBS OFF )

if( KWXFFI_BUILD_SHARED )
    message( NOTICE "Building kwxFFI as shared DLL with static wxWidgets libraries" )
    if( MSVC )
        message( NOTICE "  Using release runtime library (/MD) for DLL compatibility" )
    endif()
else()
    message( NOTICE "Building kwxFFI as static library with static wxWidgets libraries" )
endif()

# ###################### Version #######################
# Generate C++ header file with version constants for use in source code
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/src/version.h.in
    ${CMAKE_CURRENT_LIST_DIR}/src/version.h
    @ONLY
)

# Generate Windows resource file with version info for executable properties
configure_file(
    ${CMAKE_CURRENT_LIST_DIR}/src/version.rc.in
    ${CMAKE_CURRENT_LIST_DIR}/src/version.rc
    @ONLY
)

# ###################### ccache support #######################
find_program( CCACHE_PROGRAM ccache )

if( CCACHE_PROGRAM )
    message( STATUS "Using ccache: ${CCACHE_PROGRAM}" )
    set( CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}" )
    set( CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}" )

    message( NOTICE "ccache detected. Configure ccache globally for your development environment:" )
    message( NOTICE "  Recommended for all platforms:" )
    message( NOTICE "    ccache --set-config=compression=true" )
    message( NOTICE "    ccache --set-config=max_size=<appropriate for your projects>" )
    message( NOTICE "    ccache --set-config=sloppiness=pch_defines,time_macros,include_file_mtime,include_file_ctime" )

    if( MSVC )
        message( NOTICE "  Required for MSVC:" )

        message( NOTICE "    ccache --set-config=pch_external_checksum=true" )
        message( NOTICE "    ccache --set-config=depend_mode=true" )
        message( NOTICE "    ccache --set-config=\"ignore_options=/Zi /Z7 /ZI /FS /Fd*\"" )
    endif()

    message( NOTICE "  Run 'ccache --show-config' to verify current settings" )
    message( NOTICE "  Run 'ccache -s' to monitor cache usage" )
endif()

if( MSVC )
    # /O1 often results in faster code than /O2 due to CPU caching
    string( REPLACE "/O2" "/O1" cl_optimize ${CMAKE_CXX_FLAGS_RELEASE} )
    set( CMAKE_CXX_FLAGS_RELEASE ${cl_optimize} CACHE STRING "C++ Release flags" FORCE )

    string( REPLACE "/O2" "/O1" cl_optimize ${CMAKE_C_FLAGS_RELEASE} )
    set( CMAKE_C_FLAGS_RELEASE ${cl_optimize} CACHE STRING "C Release flags" FORCE )

    # Using /Z7 instead of /Zi to avoid blocking while parallel compilers write to the pdb file.
    # This can considerably speed up build times at the cost of larger object files.
    string( REPLACE "/Zi" "/Z7" z_seven ${CMAKE_CXX_FLAGS_DEBUG} )
    set( CMAKE_CXX_FLAGS_DEBUG ${z_seven} CACHE STRING "C++ Debug flags" FORCE )

    string( REPLACE "/Zi" "/Z7" z_seven ${CMAKE_C_FLAGS_DEBUG} )
    set( CMAKE_C_FLAGS_DEBUG ${z_seven} CACHE STRING "C Debug flags" FORCE )

    # Enable AddressSanitizer in Debug builds
    if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
        add_compile_options( /fsanitize=address )
        add_link_options( /fsanitize=address )
        add_link_options( /INCREMENTAL:YES /OPT:NOREF /OPT:ICF )
    endif()

    # Increase stack size for large projects with many object files
    string( APPEND CMAKE_EXE_LINKER_FLAGS " /STACK:8388608" ) # 8MB stack
elseif( UNIX AND NOT APPLE )
    # Use the package PkgConfig to detect GTK+ headers/library files
    find_package( PkgConfig REQUIRED )

    pkg_check_modules( GTK3 REQUIRED gtk+-3.0 )
    include_directories( ${GTK3_INCLUDE_DIRS} )
    link_directories( ${GTK3_LIBRARY_DIRS} )
    add_definitions( ${GTK3_CFLAGS_OTHER} )

    pkg_check_modules( X11 REQUIRED x11 )
    include_directories( ${X11_INCLUDE_DIRS} )
    link_directories( ${X11_LIBRARY_DIRS} )
    add_definitions( ${X11_CFLAGS_OTHER} )

    # Linux/BSD (gcc/clang) - optimize for size
    string( REPLACE "-O3" "-Os" cl_optimize ${CMAKE_CXX_FLAGS_RELEASE} )
    set( CMAKE_CXX_FLAGS_RELEASE ${cl_optimize} CACHE STRING "C++ Release flags" FORCE )
    string( REPLACE "-O3" "-Os" cl_optimize ${CMAKE_C_FLAGS_RELEASE} )
    set( CMAKE_C_FLAGS_RELEASE ${cl_optimize} CACHE STRING "C Release flags" FORCE )

elseif( APPLE )
    # macOS (Xcode/Clang) - optimize for size
    string( REPLACE "-O3" "-Os" cl_optimize ${CMAKE_CXX_FLAGS_RELEASE} )
    set( CMAKE_CXX_FLAGS_RELEASE ${cl_optimize} CACHE STRING "C++ Release flags" FORCE )
    string( REPLACE "-O3" "-Os" cl_optimize ${CMAKE_C_FLAGS_RELEASE} )
    set( CMAKE_C_FLAGS_RELEASE ${cl_optimize} CACHE STRING "C Release flags" FORCE )
endif()

# ###################### Set wxWidgets location macros #######################
if( WIN32 )
    set( wxWidgets_REQUIRED_COMPONENTS base core lunasvg aui html ribbon richtext propgrid webview stc xml xrc gl media net )
else()
    set( wxWidgets_REQUIRED_COMPONENTS base core lunasvg aui html ribbon richtext propgrid stc xml xrc gl media net )
endif()

include( FetchContent )

# Suppress verbose FetchContent git output (CMake 3.30+)
set(FETCHCONTENT_QUIET ON)

# Suppress verbose FetchContent git output (CMake 3.30+)
set(FETCHCONTENT_QUIET ON)

# Set wxWidgets build options BEFORE FetchContent_MakeAvailable
# wxWidgets is always built as static libraries even though kwxFFI is a shared DLL
set( wxBUILD_SHARED OFF CACHE BOOL "Build wxWidgets as static libraries" FORCE )
set( wxBUILD_USE_STATIC_RUNTIME OFF CACHE BOOL "Use dynamic runtime library" )

set( wxUSE_UNICODE_UTF8 1 CACHE BOOL "Use UTF-8 internally in wxWidgets" )
set( wxUSE_UTF8_LOCALE_ONLY 1 CACHE BOOL "Use UTF-8 locale only in wxWidgets" )
set( wxUSE_GUI ON CACHE BOOL "This is a GUI application" FORCE )
set( wxUSE_LUNASVG builtin CACHE BOOL "Use LunaSVG for rendering SVG images" FORCE )
set( wxUSE_NANOSVG OFF CACHE BOOL "Use NanoSVG for rendering SVG images" FORCE )
set( wxBUILD_INSTALL OFF CACHE BOOL "Don't build wxWidgets install" )

set( wxUSE_IFF OFF CACHE BOOL "Don't build iff image support" )

# On Windows, the only browser backend that ships with Windows 10 and 11 is IE.
# To use the Edge backend, we would need to install the WebView2 runtime.
set( wxUSE_WEBVIEW_EDGE OFF CACHE BOOL "Use wxWebView Edge backend for web viewing" )

if( WIN32 )
    set( wxUSE_WEBVIEW_IE ON CACHE BOOL "Use wxWebView IE backend for web viewing" )
    set( wxUSE_WEBVIEW ON CACHE BOOL "Use wxWidgets' web viewing classes" )
    set( wxUSE_WEBVIEW_WEBKIT OFF CACHE BOOL "Use wxWebView WebKit for web viewing" )
elseif( APPLE )
    # Apple ships with WebKit, so this should get enabled once it is verified
    # that it works
    # set( wxUSE_WEBVIEW ON CACHE BOOL "Don't use wxWidgets' web viewing classes" )
    # set( wxUSE_WEBVIEW_WEBKIT ON CACHE BOOL "Use wxWebView WebKit for web viewing" )
    set( wxUSE_WEBVIEW OFF CACHE BOOL "Don't use wxWidgets' web viewing classes" )
else()
    # Unix doesn't ship WebKit on all platforms, so we can't use it unless we
    # install it.
    set( wxUSE_WEBVIEW OFF CACHE BOOL "Don't use wxWidgets' web viewing classes" )
endif()

if( APPLE )
    # Ensure the stdlib extension macro is defined for all compilation units (including fetched
    # projects)
    add_definitions( -D__STDC_WANT_LIB_EXT1__=1 )
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__STDC_WANT_LIB_EXT1__=1" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_WANT_LIB_EXT1__=1" )

    set( wxUSE_LIBTIFF OFF CACHE BOOL "Don't use libtiff (problems compiling on Mac" )
    set( wxUSE_REGEX OFF CACHE BOOL "Don't use pcre (problems compiling on Mac" )
endif()

message( STATUS "Fetching wxWidgets (this may take awhile) ..." )

# Force wxWidgets to build in Release mode even if parent is Debug
# This ensures wx libraries use release runtime (/MD) instead of debug (/MDd)
if( MSVC AND KWXFFI_BUILD_SHARED )
    set( CMAKE_TRY_COMPILE_CONFIGURATION Release )
    # Tell wxWidgets CMakeLists to build Release
    set( CMAKE_BUILD_TYPE_INIT Release )
endif()

FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/KeyWorksRW/kwxFetch.git
    GIT_TAG dev
    GIT_SHALLOW TRUE
)

message( NOTICE "Configuring wxWidgets..." )

FetchContent_MakeAvailable( wxWidgets )

message( NOTICE "wxWidgets has been fetched and configured." )
message( STATUS "wxWidgets sources: " ${wxWidgets_SOURCE_DIR} )

# Set the library directory based on platform
if( WIN32 )
    set( WX_LIB_DIR ${wxWidgets_BUILD_DIR}/lib/vc_x64_lib )
elseif( APPLE )
    set( WX_LIB_DIR ${wxWidgets_BUILD_DIR}/lib )
elseif( UNIX )
    set( WX_LIB_DIR ${wxWidgets_BUILD_DIR}/lib )
endif()

# ###################### Libraries and Executables #######################

include( files_list.cmake )

# Library type controlled by KWXFFI_BUILD_SHARED option
if( KWXFFI_BUILD_SHARED )
    add_library( kwxFFI SHARED ${FFI_SRC_FILES} ${FFI_HDR_FILES} )
else()
    add_library( kwxFFI STATIC ${FFI_SRC_FILES} ${FFI_HDR_FILES} )
endif()

target_precompile_headers( kwxFFI PRIVATE "include/wrapper.h" )

# Force release runtime in Debug builds for shared DLL via target options
if( MSVC AND KWXFFI_BUILD_SHARED )
    target_compile_options( kwxFFI PRIVATE
        $<$<CONFIG:Debug>:/MD>  # Use release runtime in Debug builds
    )
endif()

# wxWidgets is static, so we don't define WXUSINGDLL
# target_compile_definitions( kwxFFI PRIVATE WXUSINGDLL )

if( MSVC )
    target_link_directories( kwxFFI PRIVATE ${WX_LIB_DIR} )
elseif( UNIX )
    target_compile_definitions( kwxFFI PRIVATE __WXGTK__ )
    target_link_directories( kwxFFI PRIVATE ${WX_LIB_DIR} )
endif()

# Define SHARED_LIBRARY when building as shared DLL
if( WIN32 AND KWXFFI_BUILD_SHARED )
    target_compile_definitions( kwxFFI PRIVATE SHARED_LIBRARY )
endif()

target_include_directories( kwxFFI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${wxWidgets_SOURCE_DIR}/include
)

if( WIN32 )
    target_include_directories( kwxFFI PRIVATE
        ${wxWidgets_BUILD_DIR}/lib/vc_x64_lib/mswu
    )
elseif( APPLE )
    target_include_directories( kwxFFI PRIVATE
        ${wxWidgets_BUILD_DIR}/lib/osx_cocoa-unicode-static
    )
elseif( UNIX )
    target_include_directories( kwxFFI PRIVATE
        ${wxWidgets_BUILD_DIR}/lib/gtk3_unixu-3.3/include
    )
else()
    message( FATAL_ERROR "Unsupported platform: Only WIN32, APPLE, or UNIX are supported." )
endif()

foreach( component ${wxWidgets_REQUIRED_COMPONENTS} )
    list( APPEND wxWidgets_LIBRARIES wx${component} )
endforeach()

target_link_libraries( kwxFFI PRIVATE ${wxWidgets_LIBRARIES} )

set_target_properties( kwxFFI PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib"
)
