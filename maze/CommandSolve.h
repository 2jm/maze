//------------------------------------------------------------------------------
// CommandSolve.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_COMMANDSOLVE_H
#define MAZE_COMMANDSOLVE_H


#include "Command.h"

//------------------------------------------------------------------------------
// Command Solve
//
// class representing the solve command
//
class CommandSolve : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    CommandSolve(const CommandSolve &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    CommandSolve &operator=(const CommandSolve &) = delete;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    CommandSolve();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandSolve();

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


#endif //MAZE_COMMANDSOLVE_H
