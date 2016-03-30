//
// Created by jonas on 3/28/16.
//

#ifndef MAZE_ALL_ERRORCODE_H
#define MAZE_ALL_ERRORCODE_H

enum ResultCode
{
  SUCCESS = 0,
  OUT_OF_MEMORY = 1,    // These numbers are important
  WRONG_USAGE = 2,
  FILE_COULD_NOT_BE_OPENED,
  INVALID_FILE,
  INVALID_PATH,
  FILE_COULD_NOT_BE_WRITTEN,
  INVALID_MOVE,
  BYE,
  WON,
  NO_MORE_STEPS,
  UNKNOWN_COMMAND,
  WRONG_PARAMETER_COUNT,
  WRONG_PARAMETER,
  NO_MAZE_LOADED
};

#endif //MAZE_ALL_ERRORCODE_H
