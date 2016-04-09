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
  // convert direction into the corresponding Vector2d (UP=(0,-1), RIGHT=(1,0), DOWN=(0,1), LEFT=(-1,0))
  // not needed, as compiler does this automatically when doing this: "position_ + direction;"
  //Vector2d move_vector = Vector2d(direction);

  // calculate new position
  Vector2d new_position = position_ + direction;

  while(map_[new_position].enter(position_, new_position))
  {
    position_ = new_position;
    new_position += direction;
  }

  return !(position_ == new_position);
}

Vector2d Player::getPosition()
{
  return position_;
}

void Player::setPosition(Vector2d new_position)
{
  position_ = new_position;
}







