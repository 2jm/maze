//------------------------------------------------------------------------------
// FileLoadException.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_FILELOADEXCEPTION_H
#define MAZE_ALL_FILELOADEXCEPTION_H

#include <exception>
#include <string>
#include "Message.h"

class FileLoadException : public std::exception
{
  private:
    Message::Code result_code_;

  public:
    FileLoadException(Message::Code result_code) : result_code_(result_code)
    {
    }

    Message::Code getMessage::Code() const
    {
      return result_code_;
    }

    virtual const char *what() const throw()
    {
      return Message::get(result_code_);
    }
};


#endif //MAZE_ALL_FILELOADEXCEPTION_H
