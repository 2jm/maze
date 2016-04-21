//------------------------------------------------------------------------------
// CommandLineInterface.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_COMMANDLINEINTERFACE_H
#define MAZE_COMMANDLINEINTERFACE_H

#include <vector>
#include "Message.h"

class Game;

class CommandLineInterface
{
  private:
//------------------------------------------------------------------------------
// Enum with all command Names
//
    enum Name
    {
      LOAD,
      SAVE,
      FASTMOVE,
      MOVE,
      SHOW,
      RESET,
      QUIT
    };
    const static std::string name_strings_[];

    Game &game_;

//------------------------------------------------------------------------------
// Calls the needed Commandmethod and prints the returned Message
//
// @param command string of the command, that was entered
// @param params vector of strings of all params that were entered
//
// @return false if program should be quit else true
//
    bool execute(std::string command, std::vector<std::string> params);

  public:
//------------------------------------------------------------------------------
// Constructor
//
// @param game reference of the actual game object
//
    CommandLineInterface(Game &game);

//------------------------------------------------------------------------------
// Gets the Userinput (command and params) and evaluates it
//
// @return calls execute()-method
//
    bool update();
};



#endif //MAZE_COMMANDLINEINTERFACE_H
