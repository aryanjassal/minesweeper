#pragma once

#include <chrono>
#include <cmath>
#include <vector>

#include "utils/types.hpp"

class Timer {
 public:
  // Keep track of the current time and the maximum time when the timer should
  // trigger. All time values are in milliseconds.
  f64 time_current, time_limit;

  // Unique name for each timer.
  str handle;

  // Tick the time. Note all the times are in milliseconds.
  void tick(f64 time_ms) { time_current += time_ms; }

  // Test the timer if the timer should trigger now.
  bool test() { return (time_current >= time_limit); }

  // Reset the timer.
  void reset() { time_current = 0; }
};

namespace Timers {

// Create a new timer.
Timer &create(str handle, f64 threshold_ms);

// Get a timer using its handle.
Timer &get(str handle);

// Reset the timer with the given handle. Shorthand for
// `Timers::get("handle")->reset()`
void reset(str handle);

// Test the timer with the given handle. Shorthand for
// `Timers::get("handle")->test()`
bool test(str handle);

// Tick all the timers together.
void tick(f64 time_ms);

// Get an immutable vector of all the timers created.
std::vector<Timer> all();

}  // namespace Timers

namespace timing {

// To reduce verbosity, include the entirety of std::chrono under the Time
// namespace. Make commonly used values like high_resolution_clock::time_point
// into just time_point to reduce verbosity even further. Basically, all
// std::chrono functions are now accessible under Time and time_point and now()
// by default refer to high_resolution_clock.
using namespace std::chrono;
using time_point = std::chrono::high_resolution_clock::time_point;

// Return the current time using chrono's high resolution clock. Equivalent to
// `std::chrono::high_resolution_clock::now()`
inline std::chrono::high_resolution_clock::time_point now() {
  return std::chrono::high_resolution_clock::now();
}

// Stores the delta time, or the time passed since rendering the previous frame.
extern f64 delta;

// Calculates the fps using the frame time. Frame time is calculated by dividing
// delta_time by 1000, to convert it from milliseconds to seconds. Then, inverse
// the result to give the fps. This has been done in one calculation as it is
// simpler to read.
inline u32 calculate_fps(f64 frame_time) {
  return std::round(1000.0f / frame_time);
}

}  // namespace timing
