cmake_minimum_required(VERSION 3.31)

project(kwxFFI_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ###################### Paths and tools #######################

get_filename_component(KWXFFI_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

find_package(Python3 COMPONENTS Interpreter REQUIRED)

# ###################### kwxgen code generator #######################

# Reuse the parent project's target when the tests are added from the root
# CMakeLists; otherwise pull kwxgen in as a subdirectory of this project.
if(NOT TARGET kwxgen)
    add_subdirectory("${KWXFFI_ROOT}/kwxgen" "${CMAKE_BINARY_DIR}/kwxgen")

    # kwxgen/CMakeLists.txt points the runtime output at ${CMAKE_SOURCE_DIR}/bin
    # which, for this standalone project, would be tests/bin. Keep the test
    # binaries inside the test build tree instead.
    set_target_properties(kwxgen PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()

# ###################### kwxgen_core library #######################

include("${KWXFFI_ROOT}/kwxgen/files_list.cmake")

# KWXGEN_SRC_FILES entries are repo-relative to kwxgen/; make them absolute and
# drop the executable entry point and the headers so the library holds only the
# parser and generator implementation.
set(KWXGEN_LIB_SRC "")
foreach(source_file IN LISTS KWXGEN_SRC_FILES)
    if(source_file MATCHES "src/main\\.cpp$")
        continue()
    endif()
    if(source_file MATCHES "\\.h$")
        continue()
    endif()
    list(APPEND KWXGEN_LIB_SRC "${KWXFFI_ROOT}/kwxgen/${source_file}")
endforeach()

add_library(kwxgen_core STATIC ${KWXGEN_LIB_SRC})

target_include_directories(kwxgen_core PUBLIC
    ${KWXFFI_ROOT}/kwxgen/src
    ${KWXFFI_ROOT}/kwxgen/src/lang
)

target_link_libraries(kwxgen_core PUBLIC glaze::glaze)

# ###################### Test executables #######################

add_executable(kwx_parser_tests unit/parsers_test.cpp)

target_link_libraries(kwx_parser_tests PRIVATE kwxgen_core)

# The parser tests and the checker scripts assume kwxgen exists alongside them.
add_dependencies(kwx_parser_tests kwxgen)

# ###################### Test registration #######################

enable_testing()

add_test(NAME parser_tests
    COMMAND kwx_parser_tests "${CMAKE_CURRENT_LIST_DIR}/fixtures"
)
set_tests_properties(parser_tests PROPERTIES LABELS cheap)

add_test(NAME guard_lint
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}/checks/guard_lint.py"
        --root "${KWXFFI_ROOT}"
)
set_tests_properties(guard_lint PROPERTIES LABELS cheap)

add_test(NAME guard_parity
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}/checks/guard_parity.py"
        --root "${KWXFFI_ROOT}"
)
set_tests_properties(guard_parity PROPERTIES LABELS cheap)

add_test(NAME checker_self_test
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}/checks/checker_self_test.py"
)
set_tests_properties(checker_self_test PROPERTIES LABELS cheap)

add_test(NAME export_snapshot
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}/checks/export_snapshot.py"
        --root "${KWXFFI_ROOT}"
        --kwxgen "$<TARGET_FILE:kwxgen>"
)
set_tests_properties(export_snapshot PROPERTIES LABELS cheap)

add_test(NAME deno_check
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}/checks/deno_check.py"
        --root "${KWXFFI_ROOT}"
        --kwxgen "$<TARGET_FILE:kwxgen>"
)
set_tests_properties(deno_check PROPERTIES LABELS cheap SKIP_RETURN_CODE 77)

# Runtime symbol resolution needs a shared library. A KWXFFI_BUILD_BOTH build
# names the shared target kwxFFI_shared; a plain shared build names it kwxFFI.
if(TARGET kwxFFI_shared)
    set(kwxfi_shared_target kwxFFI_shared)
elseif(TARGET kwxFFI AND KWXFFI_BUILD_SHARED)
    set(kwxfi_shared_target kwxFFI)
else()
    set(kwxfi_shared_target "")
endif()

if(kwxfi_shared_target)
    add_test(NAME symbol_resolve
        COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_LIST_DIR}/checks/symbol_resolve.py"
            --root "${KWXFFI_ROOT}"
            --library "$<TARGET_FILE:${kwxfi_shared_target}>"
            --kwxgen "$<TARGET_FILE:kwxgen>"
    )
    set_tests_properties(symbol_resolve PROPERTIES LABELS library)
endif()
