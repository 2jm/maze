//------------------------------------------------------------------------------
// TileFinish.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileFinish.h"

TileFinish::TileFinish(Vector2d position, Game &board) : Tile(position, 'x'),
                                                         board_(board)
{

}

Tile::EnterResult TileFinish::enter(Vector2d &source_position)
{
  source_position = position_;
  board_.wonGame();
  return VALID_MOVE;
}
