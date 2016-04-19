//
// Created by John on 26.03.2016.
//

#include "TileQuicksand.h"

bool TileQuicksand::enter(Vector2d source_position, Vector2d &new_position)
{
  /*
       Für die Darstellung der Treibsandfelder werden die Kleinbuchstaben 'f' bis 'j' verwendet, welche den Zahlenwerten 1 (=f) bis 5 (=j) entsprechen.
       Beim Betreten eines Treibsandfeldes werden die noch verfügbaren Schritte ('remaining steps') um die entsprechende Zahl verkleinert.
       Die Anzahl der verbleibenden Schritte kann nie unter 0 sinken. Beispiel: Verbleibende Schritte vor dem Betreten des Feldes = 3, man betritt ein Treibsandfeld i.
       Die verbleibenden Schritte sind nach dem Betreten des Feldes 0, obwohl durch das Betreten und den Treibsand der Wert -2 entstehen würde.

        Achtung: Betreten und Verlassen des Treibsandfeldes wird den üblichen Regeln entsprechend auch als jeweils 1 Schritt gewertet!
       */

  // position_ = position of the tile
  int steps_remove = character_ - 'f' + 1;
  int steps_left = board_.getStepsLeft() - steps_remove;
  board_.setStepsLeft(steps_left);

  return false;
}
