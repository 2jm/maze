//------------------------------------------------------------------------------
// CommandSave.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "CommandSave.h"
#include "Game.h"

CommandSave::CommandSave() : Command("save")
{

}

CommandSave::~CommandSave()
{

}

Message::Code CommandSave::execute(Game &board,
                                   std::vector<std::string> &params)
{
  return board.saveFile(params[0]);
}
