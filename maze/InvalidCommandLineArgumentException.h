//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_ALL_INVALIDCOMMANDLINEARGUMENTEXCEPTION_H
#define MAZE_ALL_INVALIDCOMMANDLINEARGUMENTEXCEPTION_H

#include <exception>
#include "Message.h"

class InvalidCommandLineArgumentException : public std::exception
{
  public:
    virtual const char *what() const throw()
    {
      return Message::get(ResultCode::WRONG_USAGE);
    }
};


#endif //MAZE_ALL_INVALIDCOMMANDLINEARGUMENTEXCEPTION_H
