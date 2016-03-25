//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_ALL_INVALIDCOMMANDLINEARGUMENTEXCEPTION_H
#define MAZE_ALL_INVALIDCOMMANDLINEARGUMENTEXCEPTION_H

#include <exception>

class InvalidCommandLineArgumentException : public std::exception
{
  public:
    virtual const char *what() const throw()
    {
      return "[ERR] Wrong usage: ./basic [-s <filename1>] [-m <filename2>]\n";
    }
};


#endif //MAZE_ALL_INVALIDCOMMANDLINEARGUMENTEXCEPTION_H
