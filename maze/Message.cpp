//------------------------------------------------------------------------------
// Message.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "Message.h"

//------------------------------------------------------------------------------
namespace Message
{
  //----------------------------------------------------------------------------
  const std::string MESSAGE_STRINGS[] =
  {
    "", // print nothing on success
    "[ERR] Out of memory.\n",
    "[ERR] Wrong usage: ./basic [-s <filename1>] [-m <filename2>]\n",
    "[ERR] File could not be opened.\n",
    "[ERR] Invalid file.\n",
    "[ERR] Invalid path.\n",
    "[ERR] File could not be written.\n",
    "[ERR] Invalid move.\n",
    "[ERR] No more steps possible.\n",
    "[ERR] Unknown command.\n",
    "[ERR] Wrong parameter count.\n",
    "[ERR] Wrong parameter.\n",
    "[ERR] No maze loaded.\n",
    "Bye!\n",
    "Congratulation! You solved the maze.\n",
    "Remaining Steps: ",
    "Moved Steps: "
  };

  //----------------------------------------------------------------------------
  Code print(Code message_code)
  {
    std::cout << MESSAGE_STRINGS[message_code];
    return message_code;
  }

  //----------------------------------------------------------------------------
  const char *get(Code message_code)
  {
    return MESSAGE_STRINGS[message_code].c_str();
  }
}
