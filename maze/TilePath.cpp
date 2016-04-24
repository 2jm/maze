//------------------------------------------------------------------------------
// TilePath.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TilePath.h"

//------------------------------------------------------------------------------
TilePath::TilePath(Vector2d position) : Tile(position, ' ')
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TilePath::enter(Vector2d &source_position)
{
  source_position = position_;
  return VALID_MOVE;
}
