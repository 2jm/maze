//
// Created by John on 26.03.2016.
//

#include "TilePath.h"

bool TilePath::enter(Vector2d source_position, Vector2d &new_position)
{
  // return false does not mean the tile can not be entered.
  // the tile can be entered without problem because new_position is not changed
  return false;
}

