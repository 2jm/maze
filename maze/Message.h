//------------------------------------------------------------------------------
// Message.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_MESSAGE_H
#define MAZE_ALL_MESSAGE_H

//------------------------------------------------------------------------------
// Message namespace
// This namespace holds all messages the program can print and an enum Code to
// address these messages.
//
namespace Message
{
  enum Code
  {
    SUCCESS = 0,          // These three numbers are important because they are
    OUT_OF_MEMORY = 1,    // also the return codes of the program
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
    WON,
    REMAINING_STEPS,
    MOVED_STEPS
  };

  //----------------------------------------------------------------------------
  // Prints the message with the code message_code.
  //
  // @param message_code The code of the message
  //
  // @return returns the message_code to enable the code to bubble up
  //
  Code print(Code message_code);

  //----------------------------------------------------------------------------
  // Returns the message with the code message_code.
  //
  // @return The message
  //
  const char *get(Code message_code);
};


#endif //MAZE_ALL_MESSAGE_H
