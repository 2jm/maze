//
// Created by jonas on 18.03.16.
//

#ifndef MAZE_COMMANDSAVE_H
#define MAZE_COMMANDSAVE_H


#include "Command.h"

class CommandSave : public Command
{
  public:
    CommandSave() : Command("save"){}
    virtual ~CommandSave() {};

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    ResultCode execute(Game &board, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDSAVE_H
