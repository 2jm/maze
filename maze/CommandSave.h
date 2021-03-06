//------------------------------------------------------------------------------
// CommandSave.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_COMMANDSAVE_H
#define MAZE_COMMANDSAVE_H


#include "Command.h"

//------------------------------------------------------------------------------
// Command Save
//
// class representing the save command
//
class CommandSave : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    CommandSave(const CommandSave &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    CommandSave &operator=(const CommandSave &) = delete;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    CommandSave();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandSave();

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


#endif //MAZE_COMMANDSAVE_H
