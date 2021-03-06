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

//------------------------------------------------------------------------------
// Command Quit
//
// class representing the quit command
//
class CommandQuit : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    CommandQuit(const CommandQuit &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    CommandQuit &operator=(const CommandQuit &) = delete;

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
    //
    // @param game The current game where action should be performed on
    // @param params Possible parameters needed for the execution
    //
    // @return Integer representing the success of the action
    //
    Message::Code execute(Game &game, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDQUIT_H
