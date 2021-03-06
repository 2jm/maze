//------------------------------------------------------------------------------
// CommandLoad.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_COMMANDLOAD_H
#define MAZE_COMMANDLOAD_H


#include "Command.h"

//------------------------------------------------------------------------------
// Command Load
//
// class representing the load command
//
class CommandLoad : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    CommandLoad(const CommandLoad &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    CommandLoad &operator=(const CommandLoad &) = delete;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    CommandLoad();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandLoad();

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


#endif //MAZE_COMMANDLOAD_H
