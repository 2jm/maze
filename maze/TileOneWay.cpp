//
// Created by John on 26.03.2016.
//

#include "TileOneWay.h"

bool TileOneWay::enter(Vector2d source_position, Vector2d &new_position)
{
  /*
       Dieses Feld beschränkt den Spieler in seiner Bewegungsrichtung wie folgt:
        Spitze Klammer nach links/rechts ('<', '>') bedeutet, dass das Feld nur nach links/rechts verlassen werden kann.
        Das Zirkumflex ('^', Asciiwert: 0x5E) bedeutet, dass das Feld nur nach oben verlassen werden kann.
        Der Kleinbuchstabe v bedeutet, dass das Feld nur nach unten verlassen werden kann.
       */

  return false;
}

bool TileOneWay::leave(Direction move_direction)
{
  /*Vector2d move_direction = source_position - new_position;
  if(move_direction.x() != 0)
    move_direction.setX(move_direction.x()/std::abs(move_direction.x()));
  if(move_direction.y() != 0)
    move_direction.setY(move_direction.y()/std::abs(move_direction.y()));*/

  //if(!(move_direction == Vector2d(character_)))
  Vector2d v = Vector2d(character_);
  Direction x = static_cast<Direction>(v);
  return move_direction == x;
  /*{
    // prohibit moving against tile direction
    //new_position = source_position;
  }
  return false;*/
}