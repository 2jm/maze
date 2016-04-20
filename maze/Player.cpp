//
// Created by jonas on 3/25/16.
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

  Vector2d old_position = position_;

  while(map_[position_ + direction]->enter(position_) &&
          map_[position_]->leave(direction));

  return !(position_ == old_position);
}

Vector2d Player::getPosition() const
{
  return position_;
}

void Player::setPosition(Vector2d new_position)
{
  position_ = new_position;
}







