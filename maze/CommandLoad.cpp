//
// Created by jonas on 18.03.16.
//

#include "CommandLoad.h"
#include "Game.h"
#include "FileHandler.h"

RESULT_CODE CommandLoad::execute(Game &board, std::vector<std::string> &params)
{
  if(params.size() != 1)
    return ResultCode::WRONG_PARAMETER_COUNT;

  if(!FileHandler::isValidFileName(params[0]))
    return ResultCode::WRONG_PARAMETER;

  return board.loadFile(params[0]);
}