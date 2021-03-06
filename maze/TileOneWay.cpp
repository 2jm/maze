//------------------------------------------------------------------------------
// TileOneWay.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileOneWay.h"

//------------------------------------------------------------------------------
TileOneWay::TileOneWay(Vector2d position, char character) :
        Tile(position, character)
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TileOneWay::enter(Vector2d &source_position)
{
  source_position = position_;
  return VALID_MOVE;
}

//------------------------------------------------------------------------------
bool TileOneWay::leave(const Direction move_direction)
{
  Vector2d v = Vector2d(character_);
  Direction x = static_cast<Direction>(v);
  // prohibit moving against tile direction
  return move_direction == x;
}
