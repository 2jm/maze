//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include "Game.h"
#include "CommandLineInterpreter.h"
#include "ArgumentParser.h"

class Maze
{
  private:
    Game game_;
    CommandLineInterpreter command_line_interpreter_;
    ArgumentParser argument_parser_;

  public:
    Maze();

    void init(int argc, char **argv);

    int run();
};


#endif //MAZE_MAZE_H
