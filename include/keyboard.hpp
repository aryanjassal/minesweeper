#pragma once

#include <map>

#include "utils/types.hpp"

// Register a key object which contains all the relevant data of a single key.
using kbkey_t = struct skey_t {
  bool pressed, down, released;
  bool shift, ctrl, alt, super, caps, num;

  operator bool() { return down; }
};

namespace kb {

// Register the keyboard input handler with the currently active window
void init();

// Removes the keys which are no longer being pressed by the user, potentially saving
// memory, and resets the `pressed` and `released` attributes as they should only be set for
// the duration of one update tick.
void update();

// Resets the state to the default state.
void reset();

}  // namespace kb

extern std::map<u16, kbkey_t> keys;
