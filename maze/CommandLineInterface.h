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
    bool execute(std::string command, std::vector<std::string> params);

  public:
    CommandLineInterface(Game &game);
    bool update();
};



#endif //MAZE_COMMANDLINEINTERFACE_H
