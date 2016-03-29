//
// Created by jonas on 3/29/16.
//

#include <stdexcept>
#include <limits>
#include "Convert.h"

namespace Convert
{
  unsigned int toUInt(std::string string)
  {
    if(string.find_first_not_of("0123456789") != std::string::npos)
      throw std::invalid_argument(string);

    // there is no std::stoui function.
    unsigned long number = std::stoul(string);

    if(number > std::numeric_limits<unsigned int>::max())
      throw std::out_of_range(string);
  }
}