//------------------------------------------------------------------------------
// CommandMove.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_COMMANDMOVE_H
#define MAZE_COMMANDMOVE_H


#include "Command.h"
#include "Direction.h"

//----------------------------------------------------------------------------
// Command Move
//
// class representing the move command
//
class CommandMove : public Command
{
  private:
    const std::string UP = "up";
    const std::string RIGHT = "right";
    const std::string DOWN = "down";
    const std::string LEFT = "left";

    //--------------------------------------------------------------------------
    // Converts a string into a Direction
    //
    // @param direction_string string which is transformed
    //
    // @return Direction UP, DOWN, LEFT, RIGHT or OTHER
    //
    Direction string_to_direction(const std::string direction_string) const;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    CommandMove();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandMove();

    //--------------------------------------------------------------------------
    // Executes the command.
    //
    // @param game The current game where action should be performed on
    // @param params Possible parameters needed for the execution
    //
    // @return Integer representing the success of the action
    //
    Message::Code execute(Game &game, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDMOVE_H
