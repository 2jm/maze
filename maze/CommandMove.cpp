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

#include "CommandMove.h"
#include "Convert.h"
#include "Game.h"

//------------------------------------------------------------------------------
CommandMove::CommandMove() : Command("move")
{

}

//------------------------------------------------------------------------------
CommandMove::~CommandMove()
{

}

//------------------------------------------------------------------------------
Message::Code CommandMove::execute(Game &game,
                                   std::vector<std::string> &params)
{
  if(params.size() != 1)
    return Message::WRONG_PARAMETER_COUNT;

  Direction move_direction = Convert::toDirection(params[0]);

  if(move_direction == Direction::OTHER)
    return Message::WRONG_PARAMETER;

  return game.movePlayer(move_direction);
}

//------------------------------------------------------------------------------
const std::string CommandMove::UP = "up";
const std::string CommandMove::RIGHT = "right";
const std::string CommandMove::DOWN = "down";
const std::string CommandMove::LEFT = "left";
