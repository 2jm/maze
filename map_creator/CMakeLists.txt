cmake_minimum_required(VERSION 3.3)
project(map_creator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES map_creator.cpp)
add_executable(map_creator ${SOURCE_FILES})

include_directories(../maze)

target_link_libraries(map_creator mazeLib)