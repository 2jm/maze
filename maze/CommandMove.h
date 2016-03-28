//
// Created by jonas on 18.03.16.
//

#ifndef MAZE_COMMANDMOVE_H
#define MAZE_COMMANDMOVE_H


#include "Command.h"

class CommandMove : public Command
{
  public:
    CommandMove() : Command("move"){}
    virtual ~CommandMove();

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters needed for the execution
    // @return Integer representing the success of the action
    RESULT_CODE execute(Game &board, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDMOVE_H
