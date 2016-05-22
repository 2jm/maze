//------------------------------------------------------------------------------
// TileTeleport.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileTeleport.h"

//------------------------------------------------------------------------------
TileTeleport::TileTeleport(Vector2d position, char character) :
        Tile(position, character)
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TileTeleport::enter(Vector2d &source_position)
{
  source_position = corresponding_teleport_->getPosition();
  return VALID_MOVE;
}

//------------------------------------------------------------------------------
void TileTeleport::setCorrespondingTeleport(TileTeleport *teleport)
{
  corresponding_teleport_ = teleport;
}

TileTeleport *TileTeleport::getCorrespondingTeleport()
{
  return corresponding_teleport_;
}


