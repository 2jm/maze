//
// Created by jonas on 18.03.16.
//

#include "CommandFastMove.h"
#include "Game.h"


Message::Code CommandFastMove::execute(Game &board,
                                     std::vector<std::string> &params)
{
  if(params.size() != 1)
    return Message::WRONG_PARAMETER_COUNT;

  std::string fast_move_string = params[0];

  if(!isValidFastMoveString(fast_move_string))
    return Message::WRONG_PARAMETER;

  if(!board.startFastMove())
    return Message::NO_MAZE_LOADED;

  for(auto move_direction_character : fast_move_string)
  {
    Direction move_direction = charToDirection(move_direction_character);

    if(!board.movePlayer(move_direction))
    {
      board.cancelFastMove();
      return Message::INVALID_MOVE;
    }
  }

  board.completeFastMove();

  return Message::SUCCESS;
}

bool CommandFastMove::isValidFastMoveString(std::string fast_move_string)
{
  for(auto move_direction_character : fast_move_string)
  {
    if(charToDirection(move_direction_character) == Direction::OTHER)
      return false;
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