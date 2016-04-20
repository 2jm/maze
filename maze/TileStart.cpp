//
// Created by John on 26.03.2016.
//

#include "TileStart.h"

TileStart::TileStart(Vector2d position) : Tile(position, 'o')
{

}

bool TileStart::enter(Vector2d source_position, Vector2d &new_position)
{
  // return false does not mean the tile can not be entered.
  // the tile can be entered without problem because new_position is not changed
  return false;
}