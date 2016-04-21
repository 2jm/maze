//------------------------------------------------------------------------------
// Maze.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
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
    return Message::WRONG_USAGE;
  }

  // The program runs until CommandLineInterface::update() returns false.
  while(command_line_interface_.update());

  return Message::SUCCESS;
}





