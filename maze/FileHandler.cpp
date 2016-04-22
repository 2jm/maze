//------------------------------------------------------------------------------
// FileHandler.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "FileHandler.h"

namespace FileHandler
{
  bool isValidFileName(std::string filename)
  {
    for(auto character : filename)
    {
      if (!((character >= 'A'  && character <= 'Z') ||
            (character >= 'a'  && character <= 'z') ||
            (character >= '0'  && character <= '9') ||
            character == '.' || character == '/'))
      {
        return false;
      }
    }
    return true;
  }

}