//------------------------------------------------------------------------------
// TileWall.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileWall.h"

//------------------------------------------------------------------------------
TileWall::TileWall(Vector2d position) : Tile(position, '#')
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TileWall::enter(Vector2d &source_position)
{
  // don't move into the wall
  return INVALID_MOVE;
}


