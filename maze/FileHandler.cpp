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

#include "FileHandler.h"

namespace FileHandler
{
  bool isValidFileName(std::string filename)
  {
    unsigned int loop_counter;
    for(loop_counter = 0; loop_counter < filename.length() ; ++loop_counter)
    {
      if (filename[loop_counter] < 'A'  && filename[loop_counter] > 'Z' &&
          filename[loop_counter] < 'a'  && filename[loop_counter] > 'z' &&
          filename[loop_counter] < '0'  && filename[loop_counter] > '9' &&
          filename[loop_counter] != '.' && filename[loop_counter] != '/')
      {
        return false;
      }
    }
    return true;
  }

}