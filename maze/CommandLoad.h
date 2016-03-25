//
// Created by jonas on 18.03.16.
//

#ifndef MAZE_COMMANDLOAD_H
#define MAZE_COMMANDLOAD_H


#include "Command.h"

class CommandLoad : public Command
{
  public:
    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    int execute(Game &board, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDLOAD_H
