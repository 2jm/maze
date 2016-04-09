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

  if(board.getState() == GameState::NO_MAZE_LOADED)
    return ResultCode::NO_MAZE_LOADED;

  std::string move_string = params[0];
  Direction move_direction = string_to_direction(move_string);

  if(move_direction == Direction::OTHER || !board.movePlayer(move_direction))
  {
    return ResultCode::INVALID_MOVE;
  }

//  for(auto const &value: params)
//  {
//    /* std::cout << value; ... */
//    std::cout << value << std::endl;
//  }

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

/*
Der move-Befehl bewegt den Spieler in die in <direction> angegebene Richtung, wenn der Schritt gültig ist.
Der Parameter <direction> ist genau dann valide wenn er einer der folgenden 4 Bewegungsrichtungen entspricht (case sensitive):
up
(Bewegung nach oben)
down
left
right
Zu behandelnde Fehlermeldungen (move und fastmove)
[ERR] Invalid move.\n
Sollte der angegebene Schritt/Schrittfolge ungültig sein, obwohl der Parameter gültig ist.
 */