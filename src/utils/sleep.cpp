#include "utils/sleep.hpp"

#include <chrono>
#include <thread>

#include "utils/types.hpp"

// TODO: optimise this
void smart_sleep(f64 time, f64 margin) {
  if (time <= 0) return;

  const auto t1 = std::chrono::high_resolution_clock::now();
  const auto sleep_time = std::chrono::duration<f64>(time - margin);
  std::this_thread::sleep_for(sleep_time);

  const auto t2 = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<f64> elapsed = t2 - t1;

  const auto t3 = std::chrono::high_resolution_clock::now();
  for (auto t = std::chrono::high_resolution_clock::now();
       std::chrono::duration<f64>(t - t3).count() < (time - elapsed.count());
       t = std::chrono::high_resolution_clock::now()) {
  }
}
