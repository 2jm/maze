//
// Created by John on 26.03.2016.
//

#include "TileIce.h"

bool Tile::enter(Vector2d sourcePosition, Vector2d newPosition)
{
  newPosition = position_;
  return true;
}
