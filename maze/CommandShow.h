//------------------------------------------------------------------------------
// CommandShow.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_COMMANDSHOW_H
#define MAZE_COMMANDSHOW_H


#include "Command.h"

//------------------------------------------------------------------------------
// Command Show
//
// class representing the show command
//
class CommandShow : public Command
{
  private:
    //--------------------------------------------------------------------------
    // Private copy constructor
    //
    CommandShow(const CommandShow &original);

    //--------------------------------------------------------------------------
    // Private assignment operator
    //
    CommandShow &operator=(const CommandShow &original);

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    CommandShow();

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandShow();

    //--------------------------------------------------------------------------
    // Executes the command.
    //
    // @param game The current game where action should be performed on
    // @param params Possible parameters needed for the execution
    //
    // @return Integer representing the success of the action
    //
    Message::Code execute(Game &game, std::vector<std::string> &params);
};


#endif //MAZE_COMMANDSHOW_H
