//
// Created by John on 26.03.2016.
//

#include "TileWall.h"

bool Tile::enter(Vector2d source_position, Vector2d new_position)
{
  // don't move into the wall
  new_position = source_position;
  return false;
}
