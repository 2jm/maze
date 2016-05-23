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
#include "Game.h"

//------------------------------------------------------------------------------
TileQuicksand::TileQuicksand(Vector2d position, char character, Game &game) :
        Tile(position, character),
        game_(game)
{

}

//------------------------------------------------------------------------------
Tile::EnterResult TileQuicksand::enter(Vector2d &source_position)
{
  int steps_remove = character_ - 'f' + 1;
  game_.decrementRemainingSteps(steps_remove);
  source_position = position_;
  return VALID_MOVE;
}

int TileQuicksand::getStepChange()
{
  return (character_ - 'f' + 1) * -1;
}


