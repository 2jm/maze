//
// Created by jonas on 3/26/16.
//

#ifndef MAZE_ALL_COMMANDEXCEPTION_H
#define MAZE_ALL_COMMANDEXCEPTION_H

#include <exception>
#include <string>

class CommandException : public std::exception
{
  public:
    enum ERROR_CODES
    {
      UNKNOWN_COMMAND,
      WRONG_PARAMETER_COUNT,
      WRONG_PARAMETER,
      NO_MAZE_LOADED
    };

  private:
    ERROR_CODES error_code_;
    const std::string error_strings_[4] = {
            "[ERR] Unknown command.\n",
            "[ERR] Wrong parameter count.\n",
            "[ERR] Wrong parameter.\n",
            "[ERR] No maze loaded.\n"
    };

  public:
    CommandException(ERROR_CODES error_code) : error_code_(error_code)
    {
    }

    virtual const char *what() const throw()
    {
      return error_strings_[error_code_].c_str();
    }
};


#endif //MAZE_ALL_COMMANDEXCEPTION_H
