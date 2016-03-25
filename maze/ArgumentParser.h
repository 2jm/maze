//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_ARGUMENTPARSER_H
#define MAZE_ARGUMENTPARSER_H


#include "InvalidCommandLineArgumentException.h"

class ArgumentParser
{
  private:

  public:
    void parse(int argc, const char **argv);
};


#endif //MAZE_ARGUMENTPARSER_H
