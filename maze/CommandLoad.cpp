//
// Created by jonas on 18.03.16.
//

#include "CommandLoad.h"
#include "Game.h"
#include <fstream>

RESULT_CODE CommandLoad::execute(Game &board, std::vector<std::string> &params)
{
  return board.loadFile(params[0]);
}