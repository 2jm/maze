//
// Created by jonas on 3/27/16.
//

#ifndef MAZE_ALL_MESSAGE_H
#define MAZE_ALL_MESSAGE_H

#include "ResultCode.h"

namespace Message
{
  ResultCode print(ResultCode result_code);

  const char *get(ResultCode result_code);
};


#endif //MAZE_ALL_MESSAGE_H
