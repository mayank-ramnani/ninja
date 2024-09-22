cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(hello hello.cpp)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

add_custom_target(
    tidy
    COMMAND clang-tidy ../hello.cpp --  ${CMAKE_BINARY_DIR}
    DEPENDS hello
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)