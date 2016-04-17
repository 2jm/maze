//
// Created by jonas on 18.03.16.
//

#include "CommandQuit.h"
#include <iostream>

Message::Code CommandQuit::execute(Game &board, std::vector<std::string> &params)
{
  return Message::BYE;
}

/*
quit

Parameter:
keine
Das Spiel beendet sich mit der folgenden Meldung und Exit Code 0.
Bye!\n
 */