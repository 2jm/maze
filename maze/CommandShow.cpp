//
// Created by jonas on 18.03.16.
//

#include "CommandShow.h"
#include "Game.h"

RESULT_CODE CommandShow::execute(Game &board, std::vector<std::string> &params)
{
  if(board.getState() == GameState::NO_MAZE_LOADED)
    return RESULT_CODE::NO_MAZE_LOADED;

}