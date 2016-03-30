//
// Created by jonas on 3/27/16.
//

#include "Message.h"
#include <iostream>

namespace Message
{
  const std::string strings[] = {
          "",
          "[ERR] File could not be opened.\n",
          "[ERR] Invalid file.\n",
          "[ERR] Invalid path.\n",
          "[ERR] File could not be written.\n",
          "[ERR] Invalid move.\n",
          "Bye!\n",
          "Congratulation! You solved the maze.\n",
          "[ERR] No more steps possible.\n",
          "[ERR] Out of memory.\n",
          "[ERR] Wrong usage: ./basic [-s <filename1>] [-m <filename2>]\n",
          "[ERR] Unknown command.\n",
          "[ERR] Wrong parameter count.\n",
          "[ERR] Wrong parameter.\n",
          "[ERR] No maze loaded.\n"
  };

  ResultCode print(ResultCode code)
  {
    std::cout << strings[code];
    return code;
  }

  const char *get(ResultCode result_code)
  {
    return strings[result_code].c_str();
  }


}