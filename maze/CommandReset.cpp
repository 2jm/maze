//
// Created by jonas on 18.03.16.
//

#include "CommandReset.h"
#include "Game.h"

RESULT_CODE CommandReset::execute(Game &board, std::vector<std::string> &params)
{
  if(params.size() != 0)
    return RESULT_CODE::WRONG_PARAMETER_COUNT;

  if(!board.isFileLoaded())
    return RESULT_CODE::NO_MAZE_LOADED;

  board.reset();

}