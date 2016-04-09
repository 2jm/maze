//
// Created by John on 26.03.2016.
//

#include "TileStart.h"

bool Tile::enter(Vector2d source_position, Vector2d new_position)
{
  // position_ = position of the tile, if it has already been visited
  source_position = new_position;
  return false;
}
