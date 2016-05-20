//------------------------------------------------------------------------------
// TileHole.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileHole.h"

//------------------------------------------------------------------------------
TileHole::TileHole(Vector2d position) :
        Tile(position, 's')
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TileHole::enter(Vector2d &source_position)
{
  source_position = start_tile_->getPosition();
  return VALID_MOVE;
}

//------------------------------------------------------------------------------
void TileHole::setStartTile(Tile *start)
{
  start_tile_ = start;
}
