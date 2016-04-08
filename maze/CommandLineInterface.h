//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_COMMANDLINEINTERFACE_H
#define MAZE_COMMANDLINEINTERFACE_H

#include <vector>

class Game;

class CommandLineInterface
{
  private:
    Game &game_;
    std::string input_string_;
    std::string cmd;
    std::string param;
    std::string overflow;
    bool checkLine();
    bool execute();

  public:
    CommandLineInterface(Game &game);

    bool update();
};


#endif //MAZE_COMMANDLINEINTERFACE_H
