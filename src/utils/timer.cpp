#include "utils/timer.hpp"

#include <map>
#include <vector>

#include "utils/logging.hpp"
#include "utils/types.hpp"

// Hashmap of all timer objects
std::map<str, Timer> all_timers = std::map<str, Timer>();

// Create a new timer
Timer *Timers::create(str handle, f64 threshold_ms) {
  // Check if a timer with the handle already exists.
  if (all_timers.find(handle) != all_timers.end()) {
    str s;
    error(s + "A timer with the handle '" + handle + "' already exists!");
  }

  // Initialise a new timer object.
  Timer timer;
  timer.handle = handle;
  timer.time_current = 0;
  timer.time_limit = threshold_ms;

  // Return a persistent reference.
  all_timers[handle] = timer;
  return &all_timers[handle];
}

// Get a timer from the hashmap
Timer *Timers::get(str handle) {
  if (all_timers.find(handle) == all_timers.end()) {
    str s;
    warn(s + "Timer '" + handle + "' not found.");
    return new Timer();
  }

  return &all_timers[handle];
}

// Reset a given timer using the shorthand
void Timers::reset(str handle) { Timers::get(handle)->reset(); }

// Test a given timer using the shorthand
bool Timers::test(str handle) { return Timers::get(handle)->test(); }

// Tick all the timers
void Timers::tick(f64 time_ms) {
  for (auto &pair : all_timers) {
    pair.second.tick(time_ms);
  }
}

// Get a vector of all the timers created
std::vector<Timer *> Timers::all() {
  std::vector<Timer *> out;
  for (auto &pair : all_timers) {
    out.push_back(&pair.second);
  }
  return out;
}
