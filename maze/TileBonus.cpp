//
// Created by John on 26.03.2016.
//

#include "TileBonus.h"

TileBonus::TileBonus(int steps)
{
  steps_ = steps;
}

bool Tile::enter(Vector2d sourcePosition, Vector2d newPosition)
{
  /*
       Für die Darstellung der Bonusfelder werden die Kleinbuchstaben 'a' bis 'e' verwendet, welche den Zahlenwerten 1 (=a) bis 5 (=e) entsprechen.
       Beim Betreten eines Bonusfeldes werden die noch verfügbaren Schritte ('remaining steps') um die entsprechende Zahl erhöht.
       Nach Verlassen des Feldes wird das Bonusfeld zu einem normalen Wegfeld umgewandelt.
       Mit einem Bonusfeld ist es auch möglich mehr als die ursprünglich angegebene Anzahl an verbleibenden Schritten zu erhalten.

        Achtung: Betreten und Verlassen des Bonusfeldes wird den üblichen Regeln entsprechend auch als jeweils 1 Schritt gewertet!
       */
  return false;
}
