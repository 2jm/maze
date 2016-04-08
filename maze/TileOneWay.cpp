//
// Created by John on 26.03.2016.
//

#include "TileOneWay.h"

bool TileOneWay::enter(Vector2d source_position, Vector2d new_position)
{
  /*
       Dieses Feld beschränkt den Spieler in seiner Bewegungsrichtung wie folgt:
        Spitze Klammer nach links/rechts ('<', '>') bedeutet, dass das Feld nur nach links/rechts verlassen werden kann.
        Das Zirkumflex ('^', Asciiwert: 0x5E) bedeutet, dass das Feld nur nach oben verlassen werden kann.
        Der Kleinbuchstabe v bedeutet, dass das Feld nur nach unten verlassen werden kann.
       */
  //if(new_position - source_position == Direction::UP && tile_direction_ == Direction::UP)
  if((new_position - source_position) == tile_direction_)
  {
    // new position = position of the one way tile
    //new_position = position_;
  }
  else
  {
    // prohibit moving against tile direction
    new_position = source_position;
  }
  return false;
}

TileOneWay::TileOneWay(char sign) : tile_direction_(Vector2d(sign))
{
}