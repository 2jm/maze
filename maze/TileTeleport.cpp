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

#include "TileTeleport.h"

TileTeleport::TileTeleport(Vector2d position, char character) :
        Tile(position, character)
{

}

/*
Ein Teleportfeld ist durch Großbuchstaben gekennzeichnet. Jeweils zwei Teleportfelder, die den gleichen Großbuchstaben haben, gehören zusammen.
Ein Teleport ist nur dann valide, wenn es genau zwei gleiche Großbuchstaben in einem Labyrinth gibt.
Wenn der Spieler eines der Felder betritt transportiert es ihn zum zugehörigen Gegenstück. Auf diesem Gegenstück bleibt der Spieler bis zu seinem nächsten Zug stehen.
Die Teleportfunktion kann in beide Richtungen genutzt werden.
Die Teleportation selbst verringert die verbleibende Schrittanzahl nicht. Nur das Betreten und Verlassen des Teleportfeldes zählen jeweils als 1 Schritt.
*/
bool TileTeleport::enter(Vector2d &source_position)
{
  source_position = corresponding_teleport_->getPosition();
  return false;
}

void TileTeleport::setCorrespondingTeleport(TileTeleport* teleport)
{
  corresponding_teleport_ = teleport;
}




