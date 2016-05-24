//------------------------------------------------------------------------------
// Tile.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "Tile.h"

//------------------------------------------------------------------------------
Tile::Tile(Vector2d position, char character) : position_(position),
                                                character_(character),
                                                reach_time_(99),
                                                is_inverted_(false)
{

}

//------------------------------------------------------------------------------
bool Tile::leave(const Direction move_direction)
{
  return true;
}

//------------------------------------------------------------------------------
Vector2d Tile::getPosition() const
{
  return position_;
}

//------------------------------------------------------------------------------
void Tile::reset()
{
  // does nothing
}

//------------------------------------------------------------------------------
char Tile::toChar(bool original)
{
  return character_;
}

//------------------------------------------------------------------------------
Tile::operator char() const
{
  return character_;
}

//------------------------------------------------------------------------------
int Tile::getReachTime() const
{
  return reach_time_;
}

//------------------------------------------------------------------------------
void Tile::setReachTime(int reach_time)
{
  reach_time_ = reach_time;
}

//------------------------------------------------------------------------------
int Tile::getStepChange()
{
  return 0;
}



