//
// Created by jonas on 3/27/16.
//

#ifndef MAZE_ALL_MESSAGE_H
#define MAZE_ALL_MESSAGE_H

#include "Message.h"

namespace Message
{
  enum Code
  {
    SUCCESS = 0,
    OUT_OF_MEMORY = 1,    // These numbers are important
    WRONG_USAGE = 2,
    FILE_COULD_NOT_BE_OPENED,
    INVALID_FILE,
    INVALID_PATH,
    FILE_COULD_NOT_BE_WRITTEN,
    INVALID_MOVE,
    NO_MORE_STEPS,
    UNKNOWN_COMMAND,
    WRONG_PARAMETER_COUNT,
    WRONG_PARAMETER,
    NO_MAZE_LOADED,
    BYE,
    WON
  };

  Code print(Code result_code);

  const char *get(Code result_code);
};


#endif //MAZE_ALL_MESSAGE_H
