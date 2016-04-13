//
// Created by jonas on 18.03.16.
//

#include <iostream>
#include "CommandMove.h"
#include "Game.h"
using std::cout;

CommandMove::~CommandMove(){}

ResultCode CommandMove::execute(Game &board, std::vector<std::string> &params)
{
  if(params.size() != 1)
    return ResultCode::WRONG_PARAMETER_COUNT;

  Direction move_direction = string_to_direction(params[0]);

  if(move_direction == Direction::OTHER)
    return ResultCode::WRONG_PARAMETER;

  if(board.getState() == GameState::NO_MAZE_LOADED)
    return ResultCode::NO_MAZE_LOADED;

  if(!board.movePlayer(move_direction))
    return ResultCode::INVALID_MOVE;

  return ResultCode::SUCCESS;
}

Direction CommandMove::string_to_direction(std::string direction_string)
{
  if(direction_string == "up")
  {
    return Direction::UP;
  }
  else if(direction_string == "right")
  {
    return Direction::RIGHT;
  }
  else if(direction_string == "down")
  {
    return Direction::DOWN;
  }
  else if(direction_string == "left")
  {
    return Direction::LEFT;
  }
  else
  {
    return Direction::OTHER;
  }
}