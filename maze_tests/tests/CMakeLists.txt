include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES CommandLineInterpreterTests.cpp ArgumentParserTests.cpp GameTests.cpp)

add_executable(runMazeTests ${SOURCE_FILES})

target_link_libraries(runMazeTests gtest gtest_main)
target_link_libraries(runMazeTests mazeLib)