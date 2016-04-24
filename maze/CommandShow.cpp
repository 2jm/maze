//------------------------------------------------------------------------------
// CommandShow.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "CommandShow.h"
#include "Game.h"

//------------------------------------------------------------------------------
CommandShow::CommandShow() : Command("show")
{

}

//------------------------------------------------------------------------------
CommandShow::~CommandShow()
{

}

//------------------------------------------------------------------------------
Message::Code CommandShow::execute(Game &game,
                                   std::vector<std::string> &params)
{
  if(params.size() > 1)
    return Message::WRONG_PARAMETER_COUNT;

  if(params.size() == 1 && params[0] != "more")
    return Message::WRONG_PARAMETER;

  return game.show(params.size() == 1);
}
