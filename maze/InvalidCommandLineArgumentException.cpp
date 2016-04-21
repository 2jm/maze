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

#include "InvalidCommandLineArgumentException.h"
#include "Message.h"

const char *InvalidCommandLineArgumentException::what() const throw()
{
  return Message::get(Message::WRONG_USAGE);
}
