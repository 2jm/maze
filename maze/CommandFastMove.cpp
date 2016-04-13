//
// Created by jonas on 18.03.16.
//

#include "CommandFastMove.h"
#include "Game.h"
#include "Direction.h"


ResultCode CommandFastMove::execute(Game &board,
                                     std::vector<std::string> &params)
{
  if(params.size() != 1)
    return ResultCode::WRONG_PARAMETER_COUNT;

  std::string fast_move_string = params[0];

  if(!isValidFastMoveString(fast_move_string))
    return ResultCode::WRONG_PARAMETER;

  if(!board.startFastMove())
    return ResultCode::NO_MAZE_LOADED;

  int fast_move_string_index;
  for(fast_move_string_index = 0;
      fast_move_string_index < fast_move_string.length();
      fast_move_string_index++)
  {
    Direction move_direction =
            charToDirection(fast_move_string[fast_move_string_index]);

    if(!board.movePlayer(move_direction))
    {
      board.cancelFastMove();
      return ResultCode::INVALID_MOVE;
    }
  }

  board.completeFastMove();

  return ResultCode::SUCCESS;
}

bool CommandFastMove::isValidFastMoveString(std::string fast_move_string)
{
  int fast_move_string_index;
  for(fast_move_string_index = 0;
      fast_move_string_index < fast_move_string.length();
      fast_move_string_index++)
  {
    if(charToDirection(fast_move_string[fast_move_string_index])
        == Direction::OTHER)
    {
      return false;
    }
  }

  return true;
}

Direction CommandFastMove::charToDirection(char direction_char)
{
  switch(direction_char)
  {
    case 'u':
      return Direction::UP;

    case 'r':
      return Direction::RIGHT;

    case 'd':
      return Direction::DOWN;

    case 'l':
      return Direction::LEFT;

    default:
      return Direction::OTHER;
  }
}