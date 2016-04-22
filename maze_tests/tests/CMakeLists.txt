include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES CommandLineInterpreterTests.cpp ArgumentParserTests.cpp GameTests.cpp MatrixTests.cpp ConvertTests.cpp TileTests.cpp OtherTests.cpp)

add_executable(runMazeTests ${SOURCE_FILES})

target_link_libraries(runMazeTests gtest gtest_main)
target_link_libraries(runMazeTests mazeLib)