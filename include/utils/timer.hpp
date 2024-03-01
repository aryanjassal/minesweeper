#ifndef __UTILS_TIMER_HPP__
#define __UTILS_TIMER_HPP__

#include <vector>

#include "utils/types.hpp"

class Timer {
 public:
  // Keep track of the current time and the maximum time when the timer should
  // trigger. All time values are in milliseconds.
  f64 time_current, time_limit;

  // Unique name for each timer.
  cstr handle;

  // Tick the time. Note all the times are in milliseconds.
  void tick(f64 time_ms) { time_current += time_ms; }

  // Test the timer if the timer should trigger now.
  bool test() { return (time_current >= time_limit); }

  // Reset the timer.
  void reset() { time_current = 0; }

  // Shorthand to test the timer.
  operator bool() { return test(); }
};

namespace Timers {

// Create a new timer.
Timer *create(cstr handle, f64 threshold_ms);

// Get a timer using its handle.
Timer *get(cstr handle);

// Reset the timer with the given handle. Shorthand for
// `Timers::get("handle")->reset()`
void reset(cstr handle);

// Test the timer with the given handle. Shorthand for
// `Timers::get("handle")->test()`
bool test(cstr handle);

// Tick all the timers together.
void tick(f64 time_ms);

// Get a vector of all the timers created.
std::vector<Timer *> all();

}  // namespace Timers

#endif
