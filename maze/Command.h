//------------------------------------------------------------------------------
// Filename: Command.h
//
// Description: Class representing a general command
//
// Authors: Jonas Juffinger 1531253
//          Matthias Klotz  1530653
//          Johannes Kopf   1431505
//
// Tutor: Angela Promitzer
// Group: 13624
//
// Created: 18.03.2016
// Last change: 18.03.2016
//------------------------------------------------------------------------------

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED


#include <string>
#include <vector>
#include "Message.h"

class Game;

//------------------------------------------------------------------------------
// Command
//
// base for all commands
//
class Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    Command(const Command &) = delete;

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    Command &operator=(const Command &) = delete;

    //--------------------------------------------------------------------------
    // Name of this command
    //
    std::string command_name_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Command(std::string name);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Command();

    //--------------------------------------------------------------------------
    // Executes the command.
    //
    // @param game The current game where action should be performed on
    // @param params Possible parameters needed for the execution
    //
    // @return Integer representing the success of the action
    virtual Message::Code execute(Game &game,
                                  std::vector<std::string> &params) = 0;

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    const std::string &getName() const;
};


#endif //COMMAND_H_INCLUDED
