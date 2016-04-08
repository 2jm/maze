//
// Created by John on 26.03.2016.
//

#include "TileQuicksand.h"

TileQuicksand::TileQuicksand(int steps)
{
  steps_ = steps;
}

bool Tile::enter(Vector2d source_position, Vector2d new_position)
{
  /*
       Für die Darstellung der Treibsandfelder werden die Kleinbuchstaben 'f' bis 'j' verwendet, welche den Zahlenwerten 1 (=f) bis 5 (=j) entsprechen.
       Beim Betreten eines Treibsandfeldes werden die noch verfügbaren Schritte ('remaining steps') um die entsprechende Zahl verkleinert.
       Die Anzahl der verbleibenden Schritte kann nie unter 0 sinken. Beispiel: Verbleibende Schritte vor dem Betreten des Feldes = 3, man betritt ein Treibsandfeld i.
       Die verbleibenden Schritte sind nach dem Betreten des Feldes 0, obwohl durch das Betreten und den Treibsand der Wert -2 entstehen würde.

        Achtung: Betreten und Verlassen des Treibsandfeldes wird den üblichen Regeln entsprechend auch als jeweils 1 Schritt gewertet!
       */
  new_position = position_;
  // game_.steps_left_ += steps_;
  // if(game_.steps_left_ < 0)
  //    game_steps_left_ = 0;

  // TODO: what is if int overflow occures in steps_left_? check that?
  return false;
}
