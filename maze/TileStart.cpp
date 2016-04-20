//
// Created by John on 26.03.2016.
//

#include "TileStart.h"

TileStart::TileStart(Vector2d position) : Tile(position, 'o')
{

}

bool TileStart::enter(Vector2d &source_position)
{
  source_position = position_;
  return false;
}