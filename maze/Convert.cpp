//
// Created by jonas on 3/29/16.
//

#include <stdexcept>
#include <limits>
#include "Convert.h"

namespace Convert
{
  unsigned int toUnsignedInt(std::string string)
  {
    if(string.find_first_not_of("0123456789") != std::string::npos)
      throw std::invalid_argument(string);

    // there is no std::stoui function.
    // convert to unsigned long and check if it is to big
    unsigned long number = std::stoul(string);

    if(number > std::numeric_limits<unsigned int>::max())
      throw std::out_of_range(string);

    return static_cast<unsigned int>(number);
  }

  Direction toDirection(const char direction_char)
  {
    switch(direction_char)
    {
      case 'u':
        return Direction::UP;

      case 'r':
        return Direction::RIGHT;

      case 'd':
        return Direction::DOWN;

      case 'l':
        return Direction::LEFT;

      default:
        return Direction::OTHER;
    }
  }


}