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

//----------------------------------------------------------------------------
// Command Fast Move
//
// class representing the fast move command
//
class CommandFastMove : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    CommandFastMove(const CommandFastMove &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    CommandFastMove &operator=(const CommandFastMove &) = delete;

    //--------------------------------------------------------------------------
    // Checks the entered Fastmove parameter if the string is valid
    //
    // @param fast_move_string The string with the fastmove parameter
    //
    // @return true if the String is valid
    //
    bool isValidFastMoveString(std::string fast_move_string);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    CommandFastMove();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandFastMove();

    //--------------------------------------------------------------------------
    // Executes the command.
    //
    // @param game The current game where action should be performed on
    // @param params Possible parameters needed for the execution
    //
    // @return Integer representing the success of the action
    //
    Message::Code execute(Game &game, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDFASTMOVE_H
