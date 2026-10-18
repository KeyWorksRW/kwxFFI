cmake_minimum_required(VERSION 3.31)
project(kwxgen LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ###################### sccache #######################
find_program(SCCACHE_PROGRAM sccache)
if(SCCACHE_PROGRAM)
    message(STATUS "sccache found: ${SCCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER "${SCCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${SCCACHE_PROGRAM}")
else()
    message(STATUS "sccache not found; building without a compiler cache")
endif()

if(MSVC)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:Embedded>")
endif()

include(FetchContent)

# ###################### FetchContent #######################

FetchContent_Declare(
    glaze
    GIT_REPOSITORY https://github.com/stephenberry/glaze.git
    GIT_TAG origin/main
    GIT_SHALLOW TRUE
    DOWNLOAD_NO_PROGRESS TRUE
)

FetchContent_MakeAvailable(glaze)

# ###################### Output directory #######################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>")

# ###################### Build #######################

include(files_list.cmake)

add_executable(kwxgen
    ${KWXGEN_SRC_FILES}
)

target_include_directories(kwxgen PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lang
)

target_link_libraries(kwxgen PRIVATE glaze::glaze)
