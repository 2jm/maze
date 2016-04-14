//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_COMMANDLINEINTERFACE_H
#define MAZE_COMMANDLINEINTERFACE_H

#include <vector>
#include "Message.h"

class Game;

class CommandLineInterface
{
  private:
    Game &game_;
    bool execute(std::string command, std::vector<std::string> params);

  public:
    CommandLineInterface(Game &game);
    bool update();
};

enum CommandName
{
  LOAD,
  SAVE,
  FASTMOVE,
  MOVE,
  SHOW,
  QUIT
};


#endif //MAZE_COMMANDLINEINTERFACE_H
