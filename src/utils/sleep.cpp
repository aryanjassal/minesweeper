#include "utils/sleep.hpp"

#include <atomic>
#include <chrono>
#include <thread>

#include "utils/types.hpp"

void smart_sleep(f64 time) {
  if (time <= 0) return;

  const auto start = std::chrono::steady_clock::now();
  const auto end = start + std::chrono::duration<f64>(time);

  // Sleep for 95% of the duration
  std::this_thread::sleep_for(std::chrono::duration<f64>(time * 0.95));

  // Spin-wait for the remaining time
  std::atomic_flag spin_lock = ATOMIC_FLAG_INIT;
  spin_lock.test_and_set(std::memory_order_acquire);
  while (std::chrono::steady_clock::now() < end) {
    spin_lock.clear(std::memory_order_release);
    spin_lock.test_and_set(std::memory_order_acquire);
  }
}
