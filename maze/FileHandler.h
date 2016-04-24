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
  //--------------------------------------------------------------------------
  // Checks if the entered Filename is valid
  //
  // @param filename a string with the entered path/filename
  //
  // @return true if the Filename is valid else false
  //
  bool isValidFileName(const std::string filename);

  //--------------------------------------------------------------------------
  // Opens an inputfilestream
  //
  // @param filename a string with the entered path/filename
  // @param file  inputfilestream on which the file is opened
  //
  // @return MesseageCode WRONG_PARAMETER if wrong parameters were entered
  //                      FILE_COULD_NOT_BE_OPENED if ifstream couldn't be
  //                                                opened
  //                      SUCCESS if ifstream opened successfully
  //
  Message::Code getInputFile(const std::string file_name, std::ifstream &file);

  //--------------------------------------------------------------------------
  // Opens an outputfilestream
  //
  // @param filename a string with the entered path/filename
  // @param file  outputfilestream on which the file is opened
  //
  // @return MesseageCode WRONG_PARAMETER if wrong parameters were entered
    //                      FILE_COULD_NOT_BE_WRITTEN if ofstream couldn't be
  //                                                opened
  //                      SUCCESS if ofstream opened successfully
  //
  Message::Code getOutputFile(const std::string file_name, std::ofstream &file);
};


#endif //MAZE_ALL_FILEHANDLER_H
