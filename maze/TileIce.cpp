//
// Created by John on 26.03.2016.
//

#include "TileIce.h"

bool Tile::enter(Vector2d source_position, Vector2d new_position)
{
  new_position = position_;
  return true;
}
