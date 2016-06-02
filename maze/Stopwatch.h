//
// Created by jonas on 02.06.16.
//

#ifndef MAZE_ALL_STOPWATCH_H
#define MAZE_ALL_STOPWATCH_H

#include <chrono>

namespace Stopwatch
{
  std::chrono::microseconds getElapsedTime();

  // only for debugging
  void restart();

  extern std::chrono::microseconds MAX_TIME;
};


#endif //MAZE_ALL_STOPWATCH_H
