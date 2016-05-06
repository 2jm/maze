//------------------------------------------------------------------------------
// Convert.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include <stdexcept>
#include <limits>
#include "Convert.h"
#include "CommandMove.h"

//------------------------------------------------------------------------------
namespace Convert
{
  //----------------------------------------------------------------------------
  unsigned int toUnsignedInt(const std::string string) const
  {
    if(string.find_first_not_of("0123456789") != std::string::npos)
      throw std::invalid_argument(string);

    // there is no std::stoui function.
    // convert to unsigned long and check if it is too big
    unsigned long number = std::stoul(string);

    if(number > std::numeric_limits<unsigned int>::max())
      throw std::out_of_range(string);

    return static_cast<unsigned int>(number);
  }

  //----------------------------------------------------------------------------
  Direction toDirection(const char direction_char) const
  {
    switch(direction_char)
    {
      case static_cast<char>(Direction::UP):
        return Direction::UP;

      case static_cast<char>(Direction::RIGHT):
        return Direction::RIGHT;

      case static_cast<char>(Direction::DOWN):
        return Direction::DOWN;

      case static_cast<char>(Direction::LEFT):
        return Direction::LEFT;

      default:
        return Direction::OTHER;
    }
  }

  //----------------------------------------------------------------------------
  Direction toDirection(const std::string direction_string) const
  {
    if(direction_string == CommandMove::UP)
    {
      return Direction::UP;
    }
    else if(direction_string == CommandMove::RIGHT)
    {
      return Direction::RIGHT;
    }
    else if(direction_string == CommandMove::DOWN)
    {
      return Direction::DOWN;
    }
    else if(direction_string == CommandMove::LEFT)
    {
      return Direction::LEFT;
    }
    else
    {
      return Direction::OTHER;
    }
  }
}
