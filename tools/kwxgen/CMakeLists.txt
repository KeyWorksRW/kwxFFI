cmake_minimum_required(VERSION 3.20)
project(kwxgen LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(kwxgen
    main.cpp
    class_parser.cpp
    events_parser.cpp
    keys_parser.cpp
    defs_parser.cpp
    constants_parser.cpp
    json_dump.cpp
    verify.cpp
    lang/lang_fortran.cpp
    lang/lang_go.cpp
    lang/lang_julia.cpp
    lang/lang_luajit.cpp
    lang/lang_perl.cpp
    lang/lang_rust.cpp
)

target_include_directories(kwxgen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
