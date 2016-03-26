//
// Created by John on 26.03.2016.
//

#include "TilePath.h"

bool Tile::enter(Vector2d sourcePosition, Vector2d newPosition)
{
  // new position = position of the path tile
  newPosition = position_;
  return false;
}
