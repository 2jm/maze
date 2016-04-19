//
// Created by jonas on 18.03.16.
//

#ifndef MAZE_COMMANDMOVE_H
#define MAZE_COMMANDMOVE_H


#include "Command.h"
#include "Direction.h"

class CommandMove : public Command
{
  private:
    const std::string UP = "up";
    const std::string RIGHT = "right";
    const std::string DOWN  = "down";
    const std::string LEFT = "left";

    Direction string_to_direction(const std::string direction_string) const;

  public:
    CommandMove() : Command("move"){}
    virtual ~CommandMove();

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters needed for the execution
    // @return Integer representing the success of the action
    Message::Code execute(Game &board, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDMOVE_H
