//
// Created by John on 26.03.2016.
//

#include "TilePath.h"

bool Tile::enter(Vector2d source_position, Vector2d new_position)
{
  // position_ = position of the tile
  source_position = new_position;
  return false;
}
