//
// Created by jonas on 18.03.16.
//

#include "CommandQuit.h"
#include <iostream>
using namespace std;

CommandQuit::~CommandQuit(){}

RESULT_CODE CommandQuit::execute(Game &board, std::vector<std::string> &params)
{
  cout << "Bye!\n";
  return RESULT_CODE::SUCCESS;
}

/*
quit

Parameter:
keine
Das Spiel beendet sich mit der folgenden Meldung und Exit Code 0.
Bye!\n
 */