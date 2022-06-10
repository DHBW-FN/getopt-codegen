cmake_minimum_required(VERSION 3.22)
project(CodeGenerator)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        CodeGenerator
        src/CodeGenerator.cpp
        src/XMLParser.cpp
        src/models/Option.cpp)

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