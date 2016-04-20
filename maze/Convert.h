//
// Created by jonas on 3/29/16.
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
