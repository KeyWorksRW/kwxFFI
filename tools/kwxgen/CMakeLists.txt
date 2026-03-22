cmake_minimum_required(VERSION 3.30)
project(kwxgen LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(files_list.cmake)

add_executable(kwxgen
    ${KWXGEN_SRC_FILES}
)

target_include_directories(kwxgen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
