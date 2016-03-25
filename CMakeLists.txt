cmake_minimum_required(VERSION 3.3)
project(maze_all)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES main.cpp)
add_executable(maze ${SOURCE_FILES})

include_directories(maze)

add_subdirectory(maze)
add_subdirectory(maze_tests)

target_link_libraries(maze mazeLib)