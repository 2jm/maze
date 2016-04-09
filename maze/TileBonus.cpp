//
// Created by John on 26.03.2016.
//

#include "TileBonus.h"

TileBonus::TileBonus(int steps_add, Game &board) : steps_add_(steps_add), used_(false), board_(&board)
{
}

bool TileBonus::enter(Vector2d source_position, Vector2d new_position)
{
  /*
       Für die Darstellung der Bonusfelder werden die Kleinbuchstaben 'a' bis 'e' verwendet, welche den Zahlenwerten 1 (=a) bis 5 (=e) entsprechen.
       Beim Betreten eines Bonusfeldes werden die noch verfügbaren Schritte ('remaining steps') um die entsprechende Zahl erhöht.
       Nach Verlassen des Feldes wird das Bonusfeld zu einem normalen Wegfeld umgewandelt.
       Mit einem Bonusfeld ist es auch möglich mehr als die ursprünglich angegebene Anzahl an verbleibenden Schritten zu erhalten.

        Achtung: Betreten und Verlassen des Bonusfeldes wird den üblichen Regeln entsprechend auch als jeweils 1 Schritt gewertet!
       */

  // new position = position of the path tile
  source_position = new_position;

  if(!used_)
  {
    int steps_left = board_->getStepsLeft() + steps_add_;
    board_->setStepsLeft(steps_left);
    used_ = true;
  }

  return false;
}
