//------------------------------------------------------------------------------
// Maze.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include "Game.h"
#include "CommandLineInterface.h"
#include "ArgumentParser.h"

class Maze
{
  private:
    Game game_;
    CommandLineInterface command_line_interface_;
    ArgumentParser argument_parser_;

  public:
    Maze();

    int run(int argc, char **argv);
};


#endif //MAZE_MAZE_H
