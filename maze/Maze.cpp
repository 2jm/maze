//
// Created by jonas on 3/25/16.
//

#include "Maze.h"
#include <iostream>

Maze::Maze() :
        game_(),
        command_line_interface_(game_),
        argument_parser_(game_)
{

}

int Maze::run(int argc, char **argv)
{
  try
  {
    argument_parser_.parse(argc, argv);
  }
  catch(const InvalidCommandLineArgumentException &e)
  {
    std::cout << e.what();
    return ResultCode::WRONG_USAGE;
  }

  while(command_line_interface_.update());

  return ResultCode::SUCCESS;
}




