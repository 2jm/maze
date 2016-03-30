cmake_minimum_required(VERSION 3.3)
project(maze)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Command.h Command.h Command.cpp Vector2d.cpp Vector2d.h CommandMove.cpp CommandMove.h CommandQuit.cpp CommandQuit.h CommandSave.cpp CommandSave.h CommandFastMove.cpp CommandFastMove.h Maze.cpp Maze.h Game.cpp Game.h CommandLineInterface.cpp CommandLineInterface.h ArgumentParser.cpp ArgumentParser.h Map.cpp Map.h Player.cpp Player.h GameState.h Matrix.h Tile.cpp Tile.h Direction.h InvalidCommandLineArgumentException.h TileWall.cpp TileWall.h TilePath.cpp TilePath.h TileStart.cpp TileStart.h TileFinish.cpp TileFinish.h TileIce.cpp TileIce.h TileTeleport.cpp TileTeleport.h TileOneWay.cpp TileOneWay.h TileBonus.cpp TileBonus.h TileQuicksand.cpp TileQuicksand.h Message.cpp Message.h ResultCode.h Convert.h Convert.cpp)

add_library(mazeLib STATIC ${SOURCE_FILES})