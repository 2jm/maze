//
// Created by jonas on 18.03.16.
//

#include "CommandShow.h"
#include "Game.h"

ResultCode CommandShow::execute(Game &board, std::vector<std::string> &params)
{
  if(params.size() > 1)
    return ResultCode::WRONG_PARAMETER_COUNT;

  if(params.size() == 1 && params[0] != "more")
    return ResultCode::WRONG_PARAMETER;

  if(board.getState() == GameState::NO_MAZE_LOADED)
    return ResultCode::NO_MAZE_LOADED;

  board.show(params.size() == 1);
}