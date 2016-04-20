//------------------------------------------------------------------------------
// TileOneWay.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileOneWay.h"

TileOneWay::TileOneWay(Vector2d position, char character) :
        Tile(position, character)
{

}

bool TileOneWay::enter(Vector2d &source_position)
{
  /*
       Dieses Feld beschränkt den Spieler in seiner Bewegungsrichtung wie folgt:
        Spitze Klammer nach links/rechts ('<', '>') bedeutet, dass das Feld nur nach links/rechts verlassen werden kann.
        Das Zirkumflex ('^', Asciiwert: 0x5E) bedeutet, dass das Feld nur nach oben verlassen werden kann.
        Der Kleinbuchstabe v bedeutet, dass das Feld nur nach unten verlassen werden kann.
       */
  source_position = position_;

  return false;
}

bool TileOneWay::leave(const Direction move_direction) const
{
  Vector2d v = Vector2d(character_);
  Direction x = static_cast<Direction>(v);
  // prohibit moving against tile direction
  return move_direction == x;
}