//------------------------------------------------------------------------------
// Direction.h
//
// Group: Group 13624, study assistant Angela Promitzer
//
// Authors: Jonas Juffinger (1531253)
//          Matthias Klotz (1530653)
//          Johannes Kopf (1431505)
//------------------------------------------------------------------------------
//

#ifndef MAZE_DIRECTION_H
#define MAZE_DIRECTION_H


enum class Direction : char
{
    UP = 'u',
    RIGHT = 'r',
    DOWN = 'd',
    LEFT = 'l',
    OTHER = 0
};

enum class DirectionOneWay : char
{
    UP = '^',
    RIGHT = '>',
    DOWN = 'v',
    LEFT = '<'
};


#endif //MAZE_DIRECTION_H
