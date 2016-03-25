cmake_minimum_required(VERSION 3.3)
project(maze_tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_subdirectory(lib/googletest)
add_subdirectory(tests)