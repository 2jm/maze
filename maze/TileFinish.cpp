//------------------------------------------------------------------------------
// TileFinish.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileFinish.h"

//------------------------------------------------------------------------------
TileFinish::TileFinish(Vector2d position, Game &game) : Tile(position, 'x'),
                                                         game_(game)
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TileFinish::enter(Vector2d &source_position)
{
  source_position = position_;
  game_.wonGame();
  return VALID_MOVE;
}
