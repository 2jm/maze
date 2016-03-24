//
// Created by jonas on 18.03.16.
//

#include "CommandSave.h"

CommandSave::~CommandSave(){}

int CommandSave::execute(Game &board, std::vector<std::string> &params)
{
  return 0;
}

/*
save <filename>

Speichert den aktuellen Spielstand in eine Datei, die dem oben beschriebenen Dateiformat entspricht. Das Labyrinth selbst und die erlaubte Schrittanzahl bleiben unberührt (im Vergleich zum Ladezustand).
 Der zurückgelegte Pfad wird in der Kurznotation gespeichert, die auch bei fastmove zum Einsatz kommt.

Achtung: Es darf die aktuelle Spielerposition nicht ins File gespeichert werden, da diese bei erneutem Laden aus dem gespeicherten Pfad rekonstruiert werden kann.
 Auch die erlaubte Schrittanzahl muss die ursprünglich erlaubte Schrittanzahl sein und nicht die im aktuellen Spiel verbleibenden Schritte.

Zu behandelnde Fehlermedlungen
  [ERR] File could not be written.\n
  Wenn das File nicht geöffnet oder beschrieben werden kann.
  Sollte der Dateiname nicht den Anforderungen entsprechen, wird dies als ungültiger Parameter interpretiert (siehe Allgemeine Fehlermeldungen)
 */