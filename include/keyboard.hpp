#pragma once

#include <map>

#include "utils/types.hpp"

using key = struct skey_t {
  bool pressed, down, released;
  bool shift, ctrl, alt, super, caps, num;

  operator bool() { return down; }
};

namespace kb {

// Register the keyboard input handler with the currently active window
void init();

// Remove keys which are no longer being pressed by the user, potentially saving
// memory
void clean();

// Reset the `pressed` and `released` attributes as they should only be set for
// the duration of one update tick.
void refresh();

// Does the role of both `kb::refresh()` and `kb::clean()` (in that order)
void update();

}  // namespace kb

extern std::map<u16, key> keys;
