#include "utils/sleep.hpp"

#include <chrono>
#include <thread>

void smart_sleep(double time, double margin) {
  const auto t1 = std::chrono::high_resolution_clock::now();
  const auto sleep_time = std::chrono::duration<double>(time - margin);
  std::this_thread::sleep_for(sleep_time);

  const auto t2 = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double> elapsed = t2 - t1;

  const auto t3 = std::chrono::high_resolution_clock::now();
  for (auto t = std::chrono::high_resolution_clock::now();
       std::chrono::duration<double>(t - t3).count() < (time - elapsed.count());
       t = std::chrono::high_resolution_clock::now()) {
  }
}
