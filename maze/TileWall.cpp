//
// Created by John on 26.03.2016.
//

#include "TileWall.h"

bool Tile::enter(Vector2d sourcePosition, Vector2d newPosition)
{
  // don't move into the wall
  newPosition = sourcePosition;
  return false;
}
