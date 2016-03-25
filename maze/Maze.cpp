//
// Created by jonas on 3/25/16.
//

#include "Maze.h"

Maze::Maze() :
        game_(),
        command_line_interface_(game_),
        argument_parser_(game_)
{

}

int Maze::run(int argc, char **argv)
{
  argument_parser_.parse(argc, argv);

  while(command_line_interface_.update());

  return 0;
}





