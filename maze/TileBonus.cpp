//------------------------------------------------------------------------------
// TileBonus.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileBonus.h"

//------------------------------------------------------------------------------
TileBonus::TileBonus(Vector2d position, char character, Game &board) :
        Tile(position, character),
        board_(board),
        used_(false)
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TileBonus::enter(Vector2d &source_position)
{
  if(!used_)
  {
    int steps_left = board_.getStepsLeft() + character_ - 'a' + 1;
    board_.setStepsLeft(steps_left);
    used_ = true;
  }
  source_position = position_;
  return VALID_MOVE;
}

//------------------------------------------------------------------------------
void TileBonus::reset()
{
  used_ = false;
}

//------------------------------------------------------------------------------
char TileBonus::toChar(bool original)
{
  return (!original && used_) ? ' ' : character_;
}





