//
// Created by John on 26.03.2016.
//

#include "TileTeleport.h"

bool Tile::enter(Vector2d sourcePosition, Vector2d newPosition)
{
  /*
       Ein Teleportfeld ist durch Großbuchstaben gekennzeichnet. Jeweils zwei Teleportfelder, die den gleichen Großbuchstaben haben, gehören zusammen. Ein Teleport ist nur dann valide, wenn es genau zwei gleiche Großbuchstaben in einem Labyrinth gibt.
        Wenn der Spieler eines der Felder betritt transportiert es ihn zum zugehörigen Gegenstück. Auf diesem Gegenstück bleibt der Spieler bis zu seinem nächsten Zug stehen. Die Teleportfunktion kann in beide Richtungen genutzt werden.
        Die Teleportation selbst verringert die verbleibende Schrittanzahl nicht. Nur das Betreten und Verlassen des Teleportfeldes zählen jeweils als 1 Schritt.
       */
  return false;
}
