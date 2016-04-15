//
// Created by jonas on 18.03.16.
//

#ifndef MAZE_COMMANDFASTMOVE_H
#define MAZE_COMMANDFASTMOVE_H


#include "Command.h"

enum class Direction : char;

class CommandFastMove : public Command
{
  private:

    bool isValidFastMoveString(std::string fast_move_string);

  public:
    static Direction charToDirection(char direction_char);
    CommandFastMove() : Command("fastmove")
    {
    }

    virtual ~CommandFastMove()
    {
    }

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    ResultCode execute(Game &board, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDFASTMOVE_H
