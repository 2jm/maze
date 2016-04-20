//------------------------------------------------------------------------------
// CommandReset.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
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