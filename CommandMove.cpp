//
// Created by jonas on 18.03.16.
//

#include <iostream>
#include "CommandMove.h"
using namespace std;

CommandMove::~CommandMove(){}

int CommandMove::execute(Game &board, std::vector<std::string> &params)
{
  cout << "Move" << std::endl;

//  for(auto const &value: params)
//  {
//    /* std::cout << value; ... */
//    std::cout << value << std::endl;
//  }
}

/*
Der move-Befehl bewegt den Spieler in die in <direction> angegebene Richtung, wenn der Schritt gültig ist.
Der Parameter <direction> ist genau dann valide wenn er einer der folgenden 4 Bewegungsrichtungen entspricht (case sensitive):
up
(Bewegung nach oben)
down
left
right
Zu behandelnde Fehlermeldungen (move und fastmove)
[ERR] Invalid move.\n
Sollte der angegebene Schritt/Schrittfolge ungültig sein, obwohl der Parameter gültig ist.
 */