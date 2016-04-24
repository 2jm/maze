//------------------------------------------------------------------------------
// TileIce.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileIce.h"

//------------------------------------------------------------------------------
TileIce::TileIce(Vector2d position) : Tile(position, '+')
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TileIce::enter(Vector2d &source_position)
{
  source_position = position_;
  return MOVE_AGAIN;
}
