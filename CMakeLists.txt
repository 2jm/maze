cmake_minimum_required(VERSION 3.3)
project(maze_all)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES main.cpp)
add_executable(maze ${SOURCE_FILES})

include_directories(maze)

add_subdirectory(maze)
add_subdirectory(maze_tests)
add_subdirectory(map_creator)

target_link_libraries(maze mazeLib)