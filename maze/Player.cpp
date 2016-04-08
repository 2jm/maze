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
  // TODO: i hätts so gmacht, dass z.B. der move befehle, des movePlayer vom Game aufruft, dann können dort a glei de schritte dekrementiert werden (wird in in da Game.cpp eh schon gmacht)

  // convert direction into the corresponding Vector2d (UP=(0,-1), RIGHT=(1,0), DOWN=(0,1), LEFT=(-1,0))
  Vector2d move_vector = Vector2d(direction);

  // store initial position
  Vector2d source_position = position_;

  // TODO: maybe implement "+=" operator in Vector2d, so that "position_ += move_vector;" is possible
  // set new position
  position_ = position_ + move_vector;

  Tile accessed_tile = map_.at(position_.x(), position_.y());
  bool move_again;
  do
  {
    move_again = accessed_tile.enter(position_, source_position);
  }
  while(move_again == true);
  // short form
  //while(accessed_tile_.enter(position_, source_position_));

  // Access matrix members with [x][y] or at(x, y)
  //map_.at(5, 6) = Tile();
  //map_[1][1] = Tile();

  // lower remaining steps
  // game_.steps_left_ -= 1;
  // if(GAME_STATE != GAME_WON && game_.steps_left_ <= 0) // game_.stes_left_ könnte auch -1 sein, wenn Quicksand den step left counter bereits auf 0 setzt
  //  GAME_STATE = LOST -> game lost!

  // TODO: what does this return value mean? moving was successful?
  return false;
}

Vector2d Player::getPosition()
{
  return position_;
}

void Player::setPosition(Vector2d new_position)
{
  position_ = new_position;
}







