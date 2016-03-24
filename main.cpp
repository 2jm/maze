//------------------------------------------------------------------------------
// Filename: main.cpp
//
// Description: TODO
//
// Authors: Jonas Juffinger 1531253
//          Matthias Klotz  1530653
//          Johannes Kopf   1431505
//
// Tutor: Angela Promitzer
// Group: 13624
//
// Created: 18.03.2016
// Last change: 18.03.2016
//------------------------------------------------------------------------------

#include <stdlib.h>
#include <iostream>
#include "CommandMove.h"
#include "CommandQuit.h"

using namespace std;

//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//
int main(int argc, char **argv)
{
  //TODO: wichtig!!! Die Eingabe der Befehle (Commands) erfolgt case insensitive, Parameter (argv) sind case sensitive.

  for(int i = 1; i < argc; i++)
  {
    cout << "Argv " << to_string(i) << ":" << string(argv[i]) << endl;
//    if (string(argv[i]) == "-m") {
//      break;
//    }
  }

  CommandQuit cmdQuit;
  CommandMove cmdMove;

  string line;
  while(true)
  {
    cout << "sep> "; //endl
    cin >> line;
    for (auto & c: line) c = tolower(c);
    if(line == cmdQuit.getName())
    {
      //break;
      Game game;
      vector<string> params;
      int res = cmdQuit.execute(game, params);
      break;
    }
    else if(line == cmdMove.getName())
    {
      Game game;
      vector<string> params;
      int res = cmdMove.execute(game, params);
    }
  }

  return EXIT_SUCCESS;
}