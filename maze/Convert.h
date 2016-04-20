//------------------------------------------------------------------------------
// <Filename>.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_CONVERT_H
#define MAZE_ALL_CONVERT_H

#include <string>
#include "Direction.h"

namespace Convert
{
  // Feel free to add your functions
  unsigned int toUnsignedInt(std::string string);

  Direction toDirection(const char direction_char);
}

#endif //MAZE_ALL_CONVERT_H
