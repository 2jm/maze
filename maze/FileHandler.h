//------------------------------------------------------------------------------
// FileHandler.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_FILEHANDLER_H
#define MAZE_ALL_FILEHANDLER_H

#include <string>
#include "Message.h"

namespace FileHandler
{
  bool isValidFileName(const std::string filename);

  Message::Code getInputFile(const std::string file_name, std::ifstream &file);

  Message::Code getOutputFile(const std::string file_name, std::ofstream &file);
};


#endif //MAZE_ALL_FILEHANDLER_H
