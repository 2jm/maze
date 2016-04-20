//
// Created by jonas on 3/25/16.
//

#include "Tile.h"

Tile::Tile(Vector2d position, char character) : position_(position),
                                                character_(character)
{

}

bool Tile::leave(Direction move_direction) const
{
  return true;
}

Vector2d Tile::getPosition() const
{
  return position_;
}

Tile::operator char() const
{
  return character_;
}