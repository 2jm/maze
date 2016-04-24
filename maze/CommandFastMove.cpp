//------------------------------------------------------------------------------
// CommandFastMove.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "CommandFastMove.h"
#include "Game.h"
#include "Convert.h"

//------------------------------------------------------------------------------
CommandFastMove::CommandFastMove() : Command("fastmove")
{

}

//------------------------------------------------------------------------------
CommandFastMove::~CommandFastMove()
{

}

//------------------------------------------------------------------------------
Message::Code CommandFastMove::execute(Game &game,
                                       std::vector<std::string> &params)
{
  if(params.size() != 1)
    return Message::WRONG_PARAMETER_COUNT;

  std::string fast_move_string = params[0];

  if(!isValidFastMoveString(fast_move_string))
    return Message::WRONG_PARAMETER;

  if(!game.startFastMove())
    return Message::NO_MAZE_LOADED;

  for(auto move_direction_character : fast_move_string)
  {
    Direction move_direction = Convert::toDirection(move_direction_character);
    Message::Code move_result;

    if((move_result = game.movePlayer(move_direction)) != Message::SUCCESS)
    {
      game.cancelFastMove();
      return move_result;
    }
  }

  game.completeFastMove();

  return Message::SUCCESS;
}

//------------------------------------------------------------------------------
bool CommandFastMove::isValidFastMoveString(std::string fast_move_string)
{
  for(auto move_direction_character : fast_move_string)
  {
    if(Convert::toDirection(move_direction_character) == Direction::OTHER)
      return false;
  }

  return true;
}
