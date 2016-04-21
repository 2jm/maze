#include "Map.h"
#include "TileWall.h"
#include <fstream>
#include <iostream>
#include <TileStart.h>
#include <TileFinish.h>

int main()
{
  Vector2d size(10000, 10000);
  Game game;
  Map map;
  unsigned int i, j;

  map.resize(size);

  for(i=0; i<size.x(); i++)
  {
    for(j=0; j<size.y(); j++)
    {
      Vector2d pos(i, j);
      map[pos] = std::make_shared<TileWall>(pos);
    }

    if((i % 1000) == 0)
      std::cout << "#" << std::endl;
  }

  std::cout << "map filled" << std::endl;

  Vector2d pos(2, 2);
  map[pos] = std::make_shared<TileStart>(pos);

  pos.setX(3);
  map[pos] = std::make_shared<TileFinish>(pos, game);



  std::ofstream
          output_file("huge_map.txt", std::ifstream::binary | std::ofstream::trunc);

  output_file << '\n';

  output_file << 5 << '\n';

  output_file << static_cast<std::string>(map);

  return 0;
}