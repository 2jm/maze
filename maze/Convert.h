//------------------------------------------------------------------------------
// Convert.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_CONVERT_H
#define MAZE_ALL_CONVERT_H


#include <string>
#include "Direction.h"

namespace Convert
{
  // Feel free to add your functions
  //----------------------------------------------------------------------------
  // converts a string to a unsigned int number
  //
  // @param string the string that's converted
  //
  // @return the converted number
  //
  unsigned int toUnsignedInt(std::string string);

  //----------------------------------------------------------------------------
  // converts a char to a direction
  //
  // @param direction_char a char which means direction
  //
  // @return a direction UP, DOWN, RIGHT, LEFT or OTHER
  //
  Direction toDirection(const char direction_char);
}


#endif //MAZE_ALL_CONVERT_H
