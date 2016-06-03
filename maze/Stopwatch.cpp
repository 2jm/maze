//
// Created by jonas on 02.06.16.
//

#include "Stopwatch.h"

namespace Stopwatch
{
  // start the timer when the program starts
  auto start_time = std::chrono::steady_clock::now();

  // 14s
  const std::chrono::microseconds MAX_TIME(14*1000*1000);


  void restart()
  {
    start_time = std::chrono::steady_clock::now();
  }

  std::chrono::microseconds getElapsedTime()
  {
    auto end_time = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(
                    end_time - start_time);
  }
}