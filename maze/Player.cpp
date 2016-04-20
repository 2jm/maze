//------------------------------------------------------------------------------
// Player.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "Player.h"
#include "Map.h"

Player::Player(Map &map) :
        map_(map)
{

}

bool Player::move(Direction direction)
{
  // check if the player is allowed to leave the tile
  if(!map_[position_]->leave(direction))
    return false;

  bool valid_move = false;
  Tile::EnterResult enter_result;

  while((enter_result = map_[position_ + direction]->enter(position_)) == Tile::MOVE_AGAIN &&
          map_[position_]->leave(direction))
  {
    if(enter_result != Tile::INVALID_MOVE)
      valid_move = true;
  }
  if(enter_result != Tile::INVALID_MOVE)
    valid_move = true;

  return valid_move;
}

Vector2d Player::getPosition() const
{
  return position_;
}

void Player::setPosition(Vector2d new_position)
{
  position_ = new_position;
}







