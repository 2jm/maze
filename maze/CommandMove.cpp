//------------------------------------------------------------------------------
// CommandMove.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include <iostream>
#include "CommandMove.h"
#include "Game.h"

using std::cout;

CommandMove::CommandMove() : Command("move")
{

}

CommandMove::~CommandMove()
{

}

Message::Code CommandMove::execute(Game &board,
                                   std::vector<std::string> &params)
{
  if(params.size() != 1)
    return Message::WRONG_PARAMETER_COUNT;

  Direction move_direction = string_to_direction(params[0]);

  if(move_direction == Direction::OTHER)
    return Message::WRONG_PARAMETER;

  return board.movePlayer(move_direction);
}

Direction CommandMove::string_to_direction(
        const std::string direction_string) const
{
  if(direction_string == UP)
  {
    return Direction::UP;
  }
  else if(direction_string == RIGHT)
  {
    return Direction::RIGHT;
  }
  else if(direction_string == DOWN)
  {
    return Direction::DOWN;
  }
  else if(direction_string == LEFT)
  {
    return Direction::LEFT;
  }
  else
  {
    return Direction::OTHER;
  }
}
