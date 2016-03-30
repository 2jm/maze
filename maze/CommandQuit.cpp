//
// Created by jonas on 18.03.16.
//

#include "CommandQuit.h"
#include <iostream>
using namespace std;

CommandQuit::~CommandQuit(){}

ResultCode CommandQuit::execute(Game &board, std::vector<std::string> &params)
{
  cout << "Bye!\n";
  return ResultCode::SUCCESS;
}

/*
quit

Parameter:
keine
Das Spiel beendet sich mit der folgenden Meldung und Exit Code 0.
Bye!\n
 */