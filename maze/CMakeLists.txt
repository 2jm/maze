cmake_minimum_required(VERSION 3.3)
project(maze)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Command.h Command.h Command.cpp Vector2d.cpp Vector2d.h CommandMove.cpp CommandMove.h CommandQuit.cpp CommandQuit.h CommandSave.cpp CommandSave.h Maze.cpp Maze.h Game.cpp Game.h CommandLineInterpreter.cpp CommandLineInterpreter.h ArgumentParser.cpp ArgumentParser.h Map.cpp Map.h Player.cpp Player.h GameState.h Matrix.h Tile.cpp Tile.h Direction.h Direction.cpp InvalidCommandLineArgumentException.h)

add_library(mazeLib STATIC ${SOURCE_FILES})