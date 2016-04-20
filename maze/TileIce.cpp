//
// Created by John on 26.03.2016.
//

#include "TileIce.h"

TileIce::TileIce(Vector2d position) : Tile(position, '+')
{

}

bool TileIce::enter(Vector2d &source_position)
{
  source_position = position_;
  return true;
}

