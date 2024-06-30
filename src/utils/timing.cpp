#include "utils/timing.hpp"

#include <vector>

#include "utils/id.hpp"
#include "utils/logging.hpp"
#include "utils/types.hpp"

// Set a default value for Time::delta
f64 timing::delta = 0.0f;

// Vector keeping track of all objects ever created
std::vector<Timer> all_timers = std::vector<Timer>();

Timer *timer_manager::create(str handle, f64 threshold_ms) {
  Timer timer;
  timer.handle = handle;
  timer.time_current = 0;
  timer.time_limit = threshold_ms;
  all_timers.push_back(std::move(timer));

  debug("Created new timer: " + handle);
  return &all_timers.back();
}

Timer *timer_manager::get(id::id_t id) {
  for (auto &timer : all_timers) {
    if (timer.id == id) return &timer;
  }
  return nullptr;
}

Timer *timer_manager::get(str handle) {
  for (auto &timer : all_timers) {
    if (timer.handle == handle) return &timer;
  }
  return nullptr;
}

void timer_manager::reset(id::id_t id) { timer_manager::get(id)->reset(); }
void timer_manager::reset(str handle) { timer_manager::get(handle)->reset(); }

bool timer_manager::test(id::id_t id) { return timer_manager::get(id)->test(); }
bool timer_manager::test(str handle) {
  return timer_manager::get(handle)->test();
}

void timer_manager::tick(f64 time_ms) {
  for (auto &timer : all_timers) {
    timer.tick(time_ms);
  }
}

std::vector<Timer *> timer_manager::all() {
  std::vector<Timer *> out;
  for (auto &timer : all_timers) {
    out.push_back(&timer);
  }
  return out;
}
