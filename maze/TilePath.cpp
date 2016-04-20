//
// Created by John on 26.03.2016.
//

#include "TilePath.h"

TilePath::TilePath(Vector2d position) : Tile(position, ' ')
{

}

bool TilePath::enter(Vector2d &source_position)
{
  source_position = position_;
  return false;
}

