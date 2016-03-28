//
// Created by jonas on 18.03.16.
//

#ifndef MAZE_COMMANDQUIT_H
#define MAZE_COMMANDQUIT_H


#include "Command.h"

class CommandQuit : public Command
{
  public:
    CommandQuit() : Command("quit"){}
    virtual ~CommandQuit();

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters needed for the execution
    // @return Integer representing the success of the action
    RESULT_CODE execute(Game &board, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDQUIT_H
