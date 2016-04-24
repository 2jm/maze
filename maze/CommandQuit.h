//------------------------------------------------------------------------------
// CommandQuit.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_COMMANDQUIT_H
#define MAZE_COMMANDQUIT_H


#include "Command.h"

class CommandQuit : public Command
{
  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    CommandQuit();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandQuit();

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters needed for the execution
    // @return Integer representing the success of the action
    //
    Message::Code execute(Game &board, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDQUIT_H
