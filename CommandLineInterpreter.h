//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_COMMANDLINEINTERPRETER_H
#define MAZE_COMMANDLINEINTERPRETER_H


class Game;

class CommandLineInterpreter
{
  private:
    Game &game_;

  public:
    CommandLineInterpreter(Game &game);

    bool update();
};


#endif //MAZE_COMMANDLINEINTERPRETER_H
