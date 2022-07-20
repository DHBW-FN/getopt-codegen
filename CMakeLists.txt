cmake_minimum_required(VERSION 3.22)
project(CodeGenerator)

set(CMAKE_CXX_STANDARD 14)

file(GLOB Source_Files src/*.cpp)
file(GLOB Model_Files src/models/*.cpp)

add_executable(
        CodeGenerator
        ${Source_Files}
        ${Model_Files}
)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(CodeGenerator ${Boost_LIBRARIES})
endif()

target_link_libraries(CodeGenerator xerces-c)

include_directories(src)