cmake_minimum_required(VERSION 3.22)
project(CodeGenerator)

set(CMAKE_CXX_STANDARD 14)

file(GLOB Source_Files src/sourceFiles/*.cpp)
file(GLOB Model_Files src/models/sourceFiles/*.cpp)
add_executable(
        CodeGenerator
        ${Source_Files}
        ${Model_Files}
)

file(GLOB Source_Files2 src2/*.cpp)
add_executable(
        COptionParser
        ${Source_Files2}
)

file(GLOB Source_Files2 src3/sourceFiles/*.cpp)
add_executable(
        ExampleProgram
        ${Source_Files2}
)



find_package (Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(CodeGenerator ${Boost_LIBRARIES})
endif()

if(WIN32)
    add_definitions(-DBOOST_THREAD_USE_LIB)
    target_link_libraries(CodeGenerator wsock32 ws2_32)
endif()

find_package (XercesC REQUIRED)

include_directories(src)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${XercesC_INCLUDE_DIR})

target_link_libraries(CodeGenerator ${XercesC_LIBRARIES} ${Boost_LIBRARIES})