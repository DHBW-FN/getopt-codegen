cmake_minimum_required(VERSION 3.22)
project(programming_c)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(CodeGenerator
        src/CodeGenerator.cpp
        src/XMLParser.cpp
        src/models/Option.cpp)
