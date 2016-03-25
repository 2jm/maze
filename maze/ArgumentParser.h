//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_ARGUMENTPARSER_H
#define MAZE_ARGUMENTPARSER_H


#include "InvalidCommandLineArgumentException.h"

class Game;

class ArgumentParser
{
  private:
    Game &game_;

    const char *getArgumentFileName(int argc, const char **argv, int &argument);

  public:
    ArgumentParser(Game &game);

    void parse(int argc, const char **argv);
};


#endif //MAZE_ARGUMENTPARSER_H
