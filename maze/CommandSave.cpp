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

#include "CommandSave.h"
#include "Game.h"

Message::Code CommandSave::execute(Game &board, std::vector<std::string> &params)
{
  if(board.getState() == Game::NO_MAZE_LOADED)
    return Message::NO_MAZE_LOADED;

  return board.saveFile(params[0]);
}

/*
save <filename>

 Macht alles Game.saveToFile();

Speichert den aktuellen Spielstand in eine Datei, die dem oben beschriebenen Dateiformat entspricht. Das Labyrinth selbst und die erlaubte Schrittanzahl bleiben unberührt (im Vergleich zum Ladezustand).
 Der zurückgelegte Pfad wird in der Kurznotation gespeichert, die auch bei fastmove zum Einsatz kommt.

Achtung: Es darf die aktuelle Spielerposition nicht ins File gespeichert werden, da diese bei erneutem Laden aus dem gespeicherten Pfad rekonstruiert werden kann.
 Auch die erlaubte Schrittanzahl muss die ursprünglich erlaubte Schrittanzahl sein und nicht die im aktuellen Spiel verbleibenden Schritte.

Zu behandelnde Fehlermedlungen
  [ERR] File could not be written.\n
  Wenn das File nicht geöffnet oder beschrieben werden kann.
  Sollte der Dateiname nicht den Anforderungen entsprechen, wird dies als ungültiger Parameter interpretiert (siehe Allgemeine Fehlermeldungen)
 */