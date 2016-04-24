//------------------------------------------------------------------------------
// TileQuicksand.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileQuicksand.h"

//------------------------------------------------------------------------------
TileQuicksand::TileQuicksand(Vector2d position, char character, Game &board) :
        Tile(position, character),
        board_(board)
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TileQuicksand::enter(Vector2d &source_position)
{
  int steps_remove = character_ - 'f' + 1;
  int steps_left = board_.getStepsLeft() - steps_remove;
  board_.setStepsLeft(steps_left);
  source_position = position_;
  return VALID_MOVE;
}
