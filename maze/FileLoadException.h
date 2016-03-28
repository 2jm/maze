//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_ALL_FILELOADEXCEPTION_H
#define MAZE_ALL_FILELOADEXCEPTION_H

#include <exception>
#include <string>
#include "Message.h"

class FileLoadException : public std::exception
{
  private:
    RESULT_CODE result_code_;

  public:
    FileLoadException(RESULT_CODE result_code) : result_code_(result_code)
    {
    }

    RESULT_CODE getResultCode() const
    {
      return result_code_;
    }

    virtual const char *what() const throw()
    {
      return Message::get(result_code_);
    }
};


#endif //MAZE_ALL_FILELOADEXCEPTION_H
