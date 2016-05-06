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

//------------------------------------------------------------------------------
// Convert namespace
//
// This namespace holds all methods to convert between different file types
//
namespace Convert
{
  //----------------------------------------------------------------------------
  // Converts a string to an unsigned int number
  //
  // @param string the string that's converted
  //
  // @return the converted number
  //
  unsigned int toUnsignedInt(const std::string string);

  //----------------------------------------------------------------------------
  // Converts a char to a direction
  //
  // @param direction_char A char which means direction
  //
  // @return a direction UP, DOWN, RIGHT, LEFT or OTHER
  //
  Direction toDirection(const char direction_char);
}


#endif //MAZE_ALL_CONVERT_H
