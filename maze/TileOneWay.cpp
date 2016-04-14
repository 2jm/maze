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
  //if(new_position - source_position == Direction::UP && tile_direction_ == Direction::UP)
  if((new_position - source_position) == Vector2d(character_)) // TODO: check if new_position and source_position should be changed (UP and DOWN would then be reversed, ditto LEFT and RIGHT
  {
    // position_ = position of the tile
    source_position = new_position;
  }

  // prohibit moving against tile direction -> do nothing
  //else
  //{
    //new_position = source_position;
  //}

  return false;
}
