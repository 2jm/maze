//
// Created by John on 26.03.2016.
//

#include "TileStart.h"

bool Tile::enter(Vector2d sourcePosition, Vector2d newPosition)
{
  // new position = position of the tile, if it has already been visited
  newPosition = position_;
  return false;
}
