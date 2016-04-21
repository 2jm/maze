//------------------------------------------------------------------------------
// main.cpp
//
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "Maze.h"

//------------------------------------------------------------------------------
// main function
//
// Entry point for execution. The first thing it does is create a Maze and run
// it. When there is an std::bad_alloc exception thrown somewhere in the program
// it catches it and prints an error message.
//
// @param argc argument count
// @param argv argument values
//
// @return return value for the OS
//
int main(int argc, char **argv)
{
  try
  {
    Maze maze;
    return maze.run(argc, argv);
  }
  catch(const std::bad_alloc &e)
  {
    Message::print(Message::OUT_OF_MEMORY);
    return Message::OUT_OF_MEMORY;
  }
}