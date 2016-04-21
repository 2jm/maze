//------------------------------------------------------------------------------
// ArgumentParser.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ARGUMENTPARSER_H
#define MAZE_ARGUMENTPARSER_H


#include "InvalidCommandLineArgumentException.h"

class Game;

class ArgumentParser
{
  private:
    Game &game_;

    const char *getArgumentFileName(int argc, char **argv, int &argument);

  public:
    ArgumentParser(Game &game);

    void parse(int argc, char **argv);
};


#endif //MAZE_ARGUMENTPARSER_H
