//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_COMMANDLINEINTERFACE_H
#define MAZE_COMMANDLINEINTERFACE_H


class Game;

class CommandLineInterface
{
  private:
    Game &game_;

  public:
    CommandLineInterface(Game &game);

    bool update();
};


#endif //MAZE_COMMANDLINEINTERFACE_H
