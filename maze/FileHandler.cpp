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
#include <fstream>

//------------------------------------------------------------------------------
namespace FileHandler
{
  //----------------------------------------------------------------------------
  bool isValidFileName(std::string filename)
  {
    if(filename.length() > 255)
      return false;

    for(auto character : filename)
    {
      if(!((character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z') ||
           (character >= '0' && character <= '9') ||
           character == '.' || character == '/'))
      {
        return false;
      }
    }
    return true;
  }

  //----------------------------------------------------------------------------
  Message::Code getInputFile(const std::string file_name, std::ifstream &file)
  {
    if(!FileHandler::isValidFileName(file_name))
      return Message::WRONG_PARAMETER;

    file.open(file_name, std::ifstream::binary);

    if(file.fail())
      return Message::FILE_COULD_NOT_BE_OPENED;

    return Message::SUCCESS;
  }

  //----------------------------------------------------------------------------
  Message::Code getOutputFile(const std::string file_name, std::ofstream &file)
  {
    if(!FileHandler::isValidFileName(file_name))
      return Message::WRONG_PARAMETER;

    file.open(file_name, std::ifstream::binary | std::ofstream::trunc);

    if(file.fail())
      return Message::FILE_COULD_NOT_BE_WRITTEN;

    return Message::SUCCESS;
  }
}
