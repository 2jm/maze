//------------------------------------------------------------------------------
// CommandWhoAmI.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_COMMANDWHOAMI_H
#define MAZE_COMMANDWHOAMI_H


#include "Command.h"

//------------------------------------------------------------------------------
// Command WhoAmI
//
// class representing the whoami command
//
class CommandWhoAmI : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    CommandWhoAmI(const CommandWhoAmI &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    CommandWhoAmI &operator=(const CommandWhoAmI &) = delete;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    CommandWhoAmI();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandWhoAmI();

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


#endif //MAZE_COMMANDWHOAMI_H
