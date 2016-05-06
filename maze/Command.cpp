//------------------------------------------------------------------------------
// Filename: Command.cpp
//
// Description: Class representing a general command
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

#include "Command.h"

//------------------------------------------------------------------------------
Command::Command(std::string name) : command_name_(name)
{
}

//------------------------------------------------------------------------------
Command::~Command()
{
}

//------------------------------------------------------------------------------
const std::string &Command::getName() const
{
  return command_name_;
}