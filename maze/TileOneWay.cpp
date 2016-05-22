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
#include "Direction.h"

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
  Direction x = static_cast<Direction>(v);;

  if(is_inverted_)
  {
    if(x == Direction::UP)
      x = Direction::DOWN;

    if(x == Direction::DOWN)
      x = Direction::UP;

    if(x == Direction::LEFT)
      x = Direction::RIGHT;

    if(x == Direction::RIGHT)
      x = Direction::LEFT;
  }


  // prohibit moving against tile direction
  return move_direction == x;
}
