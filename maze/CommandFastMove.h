//------------------------------------------------------------------------------
// CommandFastMove.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_COMMANDFASTMOVE_H
#define MAZE_COMMANDFASTMOVE_H


#include "Command.h"

enum class Direction : char;

class CommandFastMove : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Checks the entered Fastmove parameter if the string is valid
    // @param fast_move_string The string with the fastmove parameter
    // @return true if the String is valid
    //
    bool isValidFastMoveString(std::string fast_move_string);

  public:
    //--------------------------------------------------------------------------
    //Constructor
    //
    CommandFastMove();

    //--------------------------------------------------------------------------
    //Destructor
    //
    virtual ~CommandFastMove();

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters needed for the execution
    // @return Integer representing the success of the action
    //
    Message::Code execute(Game &board, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDFASTMOVE_H
