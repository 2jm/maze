//
// Created by jonas on 3/29/16.
//

#include <stdexcept>
#include "Convert.h"

namespace Convert
{
  unsigned int toUInt(std::string string)
  {
    if(string.find_first_not_of("0123456789") != std::string::npos)
      throw std::invalid_argument(string);

    unsigned long number = std::stoul(string);
  }
}