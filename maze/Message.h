//
// Created by jonas on 3/27/16.
//

#ifndef MAZE_ALL_MESSAGE_H
#define MAZE_ALL_MESSAGE_H

#include "ResultCode.h"

namespace Message
{
  void print(RESULT_CODE result_code);

  const char *get(RESULT_CODE result_code);
};


#endif //MAZE_ALL_MESSAGE_H
