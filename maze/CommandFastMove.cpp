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

  if(board.getState() == GameState::NO_MAZE_LOADED)
    return ResultCode::NO_MAZE_LOADED;

  std::string fast_move_string = params[0];
  int fast_move_string_index;

  board.startFastMove();

  for(fast_move_string_index = 0;
      fast_move_string_index < fast_move_string.length();
      fast_move_string_index++)
  {
    Direction move_direction =
            char_to_direction(fast_move_string[fast_move_string_index]);

    // This works because board.movePlayer is not called when
    // move_direction = Direction::OTHER
    if(move_direction == Direction::OTHER ||
       !board.movePlayer(move_direction))
    {
      board.cancelFastMove();
      return ResultCode::INVALID_MOVE;
    }
  }

  board.completeFastMove();

  return ResultCode::SUCCESS;
}


Direction CommandFastMove::char_to_direction(char direction_char)
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