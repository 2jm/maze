//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_ALL_FILELOADEXCEPTION_H
#define MAZE_ALL_FILELOADEXCEPTION_H

#include <exception>
#include <string>

class FileLoadException : public std::exception
{
  public:
    enum ERROR_CODES
    {
      COULD_NOT_BE_OPENED,
      INVALID_FILE,
      INVALID_PATH
    };

  private:
    ERROR_CODES error_code_;
    const std::string error_strings_[3] = {
            "[ERR] File could not be opened.\n",
            "[ERR] Invalid file.\n",
            "[ERR] Invalid path.\n"
    };

  public:
    FileLoadException(ERROR_CODES error_code) : error_code_(error_code)
    {
    }

    virtual const char *what() const throw()
    {
      return error_strings_[error_code_].c_str();
    }
};


#endif //MAZE_ALL_FILELOADEXCEPTION_H
