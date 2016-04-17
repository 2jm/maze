//
// Created by jonas on 18.03.16.
//

#include "CommandReset.h"
#include "Game.h"

Message::Code CommandReset::execute(Game &board, std::vector<std::string> &params)
{
  if(params.size() != 0)
    return Message::WRONG_PARAMETER_COUNT;

  if(board.getState() == Game::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  board.reset();

  return Message::SUCCESS;
}