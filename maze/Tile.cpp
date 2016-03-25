//
// Created by jonas on 3/25/16.
//

#include "Tile.h"

// return value tells, if on the new tile enter should be called again (needed for the ice tile, if the player should move from tile to tile without having a chance to interact (move) again
bool Tile::enter(Vector2d sourcePosition, Vector2d newPosition)
{
  bool ret = false;
  switch(tileType_)
  {
    case Wall:
      // don't move into the wall
      newPosition = sourcePosition;
      break;
    case Path:
      // new position = position of the tile
      newPosition = position_;
      break;
    case Start:
      // new position = position of the tile, if it has already been visited
      newPosition = position_;
      break;
    case Finish:
      // game is won
      // TODO
      break;
    case Ice:
      newPosition = position_;
      ret = true;
      break;
    case Teleport:
      /*
       Ein Teleportfeld ist durch Großbuchstaben gekennzeichnet. Jeweils zwei Teleportfelder, die den gleichen Großbuchstaben haben, gehören zusammen. Ein Teleport ist nur dann valide, wenn es genau zwei gleiche Großbuchstaben in einem Labyrinth gibt.
        Wenn der Spieler eines der Felder betritt transportiert es ihn zum zugehörigen Gegenstück. Auf diesem Gegenstück bleibt der Spieler bis zu seinem nächsten Zug stehen. Die Teleportfunktion kann in beide Richtungen genutzt werden.
        Die Teleportation selbst verringert die verbleibende Schrittanzahl nicht. Nur das Betreten und Verlassen des Teleportfeldes zählen jeweils als 1 Schritt.
       */
      break;
    case OneWay:
      /*
       Dieses Feld beschränkt den Spieler in seiner Bewegungsrichtung wie folgt:
        Spitze Klammer nach links/rechts ('<', '>') bedeutet, dass das Feld nur nach links/rechts verlassen werden kann.
        Das Zirkumflex ('^', Asciiwert: 0x5E) bedeutet, dass das Feld nur nach oben verlassen werden kann.
        Der Kleinbuchstabe v bedeutet, dass das Feld nur nach unten verlassen werden kann.
       */
      break;
    case Bonus:
      /*
       Für die Darstellung der Bonusfelder werden die Kleinbuchstaben 'a' bis 'e' verwendet, welche den Zahlenwerten 1 (=a) bis 5 (=e) entsprechen. Beim Betreten eines Bonusfeldes werden die noch verfügbaren Schritte ('remaining steps') um die entsprechende Zahl erhöht. Nach Verlassen des Feldes wird das Bonusfeld zu einem normalen Wegfeld umgewandelt. Mit einem Bonusfeld ist es auch möglich mehr als die ursprünglich angegebene Anzahl an verbleibenden Schritten zu erhalten.
        Achtung: Betreten und Verlassen des Bonusfeldes wird den üblichen Regeln entsprechend auch als jeweils 1 Schritt gewertet!
       */
      break;
    case Quicksand:
      /*
       Für die Darstellung der Treibsandfelder werden die Kleinbuchstaben 'f' bis 'j' verwendet, welche den Zahlenwerten 1 (=f) bis 5 (=j) entsprechen. Beim Betreten eines Treibsandfeldes werden die noch verfügbaren Schritte ('remaining steps') um die entsprechende Zahl verkleinert. Die Anzahl der verbleibenden Schritte kann nie unter 0 sinken. Beispiel: Verbleibende Schritte vor dem Betreten des Feldes = 3, man betritt ein Treibsandfeld i. Die verbleibenden Schritte sind nach dem Betreten des Feldes 0, obwohl durch das Betreten und den Treibsand der Wert -2 entstehen würde.
        Achtung: Betreten und Verlassen des Treibsandfeldes wird en üblichen Regeln entsprechend auch als jeweils 1 Schritt gewertet!
       */
      break;
  }
  return ret;
}