//
// Created by jonas on 5/20/16.
//

#include "TileCounter.h"

TileCounter::TileCounter(Vector2d position, char character) :
        Tile(position, character),
        counter_value_(character - '0')
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TileCounter::enter(Vector2d &source_position)
{
  if(counter_value_ == 0)
    return INVALID_MOVE;

  source_position = position_;
  return VALID_MOVE;
}

//------------------------------------------------------------------------------
bool TileCounter::leave(const Direction move_direction)
{
  if(counter_value_ > 0)
    counter_value_--;

  return true;
}

//------------------------------------------------------------------------------
void TileCounter::reset()
{
  counter_value_ = character_ - '0';
}

//------------------------------------------------------------------------------
char TileCounter::toChar(bool original)
{
  if(original)
    return character_;

  if(counter_value_ == 0)
    return '#';

  return counter_value_ + '0';
}

void TileCounter::set0()
{
  counter_value_ = 0;
}


