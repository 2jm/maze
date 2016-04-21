//------------------------------------------------------------------------------
// InvalidCommandLineArgumentException.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
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
      return Message::get(Message::WRONG_USAGE);
    }
};


#endif //MAZE_ALL_INVALIDCOMMANDLINEARGUMENTEXCEPTION_H
