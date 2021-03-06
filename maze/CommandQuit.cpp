//------------------------------------------------------------------------------
// CommandQuit.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "CommandQuit.h"

//------------------------------------------------------------------------------
CommandQuit::CommandQuit() : Command("quit")
{

}

//------------------------------------------------------------------------------
CommandQuit::~CommandQuit()
{

}

//------------------------------------------------------------------------------
Message::Code CommandQuit::execute(Game &game,
                                   std::vector<std::string> &params)
{
  if(params.size() != 0)
    return Message::WRONG_PARAMETER_COUNT;

  return Message::BYE;
}
