//
// Created by jonas on 18.03.16.
//

#ifndef MAZE_COMMANDSHOW_H
#define MAZE_COMMANDSHOW_H


#include "Command.h"

class CommandShow : public Command
{
  public:
    CommandShow() : Command("show"){}
    virtual ~CommandShow() {};

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    Message::Code execute(Game &board, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDSHOW_H
