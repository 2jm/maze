//------------------------------------------------------------------------------
// ArgumentParser.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ARGUMENTPARSER_H
#define MAZE_ARGUMENTPARSER_H


#include "InvalidCommandLineArgumentException.h"

class Game;

//------------------------------------------------------------------------------
// ArgumentParser class
// The argument parser class parses and processes the command line arguments.
//
class ArgumentParser
{
  private:
    //--------------------------------------------------------------------------
    /// Reference to the current game
    //
    Game &game_;

    //--------------------------------------------------------------------------
    // Get the argument file name
    // This is called after a -s or -m is detected. It returns following
    // argument if it is existing.
    //
    // @param argc The argument count
    // @param argv The arguments
    //
    // @param argument_index The index of the currently checked argument
    //
    const char *getArgumentFileName(int argc, char **argv, int &argument_index);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    ArgumentParser(Game &game);

    //----------------------------------------------------------------------
    // Copy Constructor
    //
    // @param original The original ArgumentParser to copy
    //
    ArgumentParser(const ArgumentParser &original);

    //----------------------------------------------------------------------
    // Parse method
    // This method parses and processes the command line arguments.
    //
    // @param argc The argument count
    // @param argv The arguments
    //
    void parse(int argc, char **argv);
};


#endif //MAZE_ARGUMENTPARSER_H
