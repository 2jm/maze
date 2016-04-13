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
    std::string input_string_;
    std::string cmd;
    std::vector<std::string> params;
    //std::string overflow;
    //bool checkLine();
    bool execute();

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
