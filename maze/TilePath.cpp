//
// Created by John on 26.03.2016.
//

#include "TilePath.h"

bool Tile::enter(Vector2d source_position, Vector2d new_position)
{
  // new position = position of the path tile
  new_position = position_;
  return false;
}
