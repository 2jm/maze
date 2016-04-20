//
// Created by John on 26.03.2016.
//

#include "TileWall.h"

TileWall::TileWall(Vector2d position) : Tile(position, '#')
{

}

bool TileWall::enter(Vector2d &source_position)
{
  // don't move into the wall
  return false;
}


