//------------------------------------------------------------------------------
// InvalidCommandLineArgumentException.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_ALL_INVALIDCOMMANDLINEARGUMENTEXCEPTION_H
#define MAZE_ALL_INVALIDCOMMANDLINEARGUMENTEXCEPTION_H


#include <exception>

//------------------------------------------------------------------------------
// Invalid Command Line Argument Exception
//
// Custom made exception that is thrown if something went wrong while
// parsing the command line arguments
//
class InvalidCommandLineArgumentException : public std::exception
{
  public:
    //--------------------------------------------------------------------------
    // Use default Constructor
    //
    InvalidCommandLineArgumentException() = default;

    //--------------------------------------------------------------------------
    // Use default copy constructor
    //
    InvalidCommandLineArgumentException(
            const InvalidCommandLineArgumentException &) = default;

    //--------------------------------------------------------------------------
    // Use default assignment operator
    //
    InvalidCommandLineArgumentException &operator=(
            const InvalidCommandLineArgumentException &) = default;

    //--------------------------------------------------------------------------
    // Tells what went wrong
    //
    // @return Message representing what went wrong
    //
    virtual const char *what() const throw();
};


#endif //MAZE_ALL_INVALIDCOMMANDLINEARGUMENTEXCEPTION_H
