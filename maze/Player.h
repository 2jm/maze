//------------------------------------------------------------------------------
// Player.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_PLAYER_H
#define MAZE_PLAYER_H


#include "Vector2d.h"
#include "Direction.h"

class Map;

//------------------------------------------------------------------------------
// Player class
//
// class representing the player of the game with the current position on the
// map
//
class Player
{
  private:
    //--------------------------------------------------------------------------
    /// Current position of the player
    //
    Vector2d position_;
    //--------------------------------------------------------------------------
    /// Reference to the current loaded map
    //
    Map &map_;

  public:
    //--------------------------------------------------------------------------
    // Constructor
    //
    Player(Map &map);

    //--------------------------------------------------------------------------
    // Moves the player in the given direction
    //
    // @param direction The current moving direction of the player
    //
    // @return bool Tells if the move is valid
    //
    bool move(Direction direction);

    //--------------------------------------------------------------------------
    // Getter Methods
    //
    Vector2d getPosition() const;

    //--------------------------------------------------------------------------
    // Setter Methods
    //
    void setPosition(Vector2d);
};


#endif //MAZE_PLAYER_H
