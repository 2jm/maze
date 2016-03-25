//
// Created by jonas on 3/25/16.
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
