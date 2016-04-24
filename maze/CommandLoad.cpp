//------------------------------------------------------------------------------
// CommandLoad.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "CommandLoad.h"
#include "Game.h"

CommandLoad::CommandLoad() : Command("load")
{

}

CommandLoad::~CommandLoad()
{

}

Message::Code CommandLoad::execute(Game &game,
                                   std::vector<std::string> &params)
{
  if(params.size() != 1)
    return Message::WRONG_PARAMETER_COUNT;

  return game.loadFile(params[0]);
}
