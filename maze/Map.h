//
// Created by jonas on 3/25/16.
//

#ifndef MAZE_MAP_H
#define MAZE_MAP_H

#include "Matrix.h"
#include "Tile.h"
#include <string>
//#include <string>

class Map : public Matrix<Tile>
{
  //private:

/*  public:
    void loadFromString(std::string string);
    void check();
    Tile getEndTile();
    Tile getStartTile();
    Tile getTeleporterPair(char name);*/

  public:
    Map()
    {
    }

    bool loadFromString(std::string map_string);

    std::string saveToString();
};


#endif //MAZE_MAP_H
