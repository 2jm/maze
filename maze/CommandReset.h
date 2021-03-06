//------------------------------------------------------------------------------
// CommandReset.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_COMMANDRESET_H
#define MAZE_COMMANDRESET_H


#include "Command.h"

//------------------------------------------------------------------------------
// Command Reset
//
// class representing the reset command
//
class CommandReset : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    CommandReset(const CommandReset &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    CommandReset &operator=(const CommandReset &) = delete;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    CommandReset();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandReset();

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


#endif //MAZE_COMMANDRESET_H
