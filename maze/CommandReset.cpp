//
// Created by jonas on 18.03.16.
//

#include "CommandReset.h"
#include "Game.h"

ResultCode CommandReset::execute(Game &board, std::vector<std::string> &params)
{
  if(params.size() != 0)
    return RESULT_CODE::WRONG_PARAMETER_COUNT;

  if(board.getState() == GameState::NO_MAZE_LOADED)
    return RESULT_CODE::NO_MAZE_LOADED;

  board.reset();

}