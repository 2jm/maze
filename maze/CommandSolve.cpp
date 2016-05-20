//------------------------------------------------------------------------------
// CommandSolve.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "CommandSolve.h"
#include "Game.h"

//------------------------------------------------------------------------------
CommandSolve::CommandSolve() : Command("solve")
{

}

//------------------------------------------------------------------------------
CommandSolve::~CommandSolve()
{

}

//------------------------------------------------------------------------------
Message::Code CommandSolve::execute(Game &game,
                                   std::vector<std::string> &params)
{
  if(params.size() > 1)
    return Message::WRONG_PARAMETER_COUNT;

  if(params.size() == 1 && params[0] != "silent")
    return Message::WRONG_PARAMETER;

  return game.solve(params.size() == 1);
}
