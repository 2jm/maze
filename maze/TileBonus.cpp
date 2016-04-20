//------------------------------------------------------------------------------
// <Filename>.cpp
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
// Matthias Klotz (1530653)
// Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#include "TileBonus.h"

TileBonus::TileBonus(Vector2d position, char character, Game &board) :
        Tile(position, character),
        board_(board),
        used_(false)
{

}


bool TileBonus::enter(Vector2d &source_position)
{
  /*
       Für die Darstellung der Bonusfelder werden die Kleinbuchstaben 'a' bis 'e' verwendet, welche den Zahlenwerten 1 (=a) bis 5 (=e) entsprechen.
       Beim Betreten eines Bonusfeldes werden die noch verfügbaren Schritte ('remaining steps') um die entsprechende Zahl erhöht.
       Nach Verlassen des Feldes wird das Bonusfeld zu einem normalen Wegfeld umgewandelt.
       Mit einem Bonusfeld ist es auch möglich mehr als die ursprünglich angegebene Anzahl an verbleibenden Schritten zu erhalten.

        Achtung: Betreten und Verlassen des Bonusfeldes wird den üblichen Regeln entsprechend auch als jeweils 1 Schritt gewertet!
       */

  if(!used_)
  {
    int steps_left = board_.getStepsLeft() + character_ - 'a' + 1;
    board_.setStepsLeft(steps_left);
    used_ = true;
  }

  source_position = position_;

  return false;
}

TileBonus::operator char() const
{
  return (used_) ? ' ' : character_;
}

void TileBonus::setUsed(bool used)
{
  used_ = used;
}



