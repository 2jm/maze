//
// Created by jonas on 18.03.16.
//

#include "CommandShow.h"
#include "Game.h"

ResultCode CommandShow::execute(Game &board, std::vector<std::string> &params)
{
  // check params count

  if(board.getState() == GameState::NO_MAZE_LOADED)
    return ResultCode::NO_MAZE_LOADED;

  board.show();

  // check params
}