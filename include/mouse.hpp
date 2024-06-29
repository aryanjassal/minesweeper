#pragma once

#include "glm/glm.hpp"  // IWYU pragma: keep

using mousebuttons_t = struct smousebuttons_t {
  bool left, left_down, left_up;
  bool right, right_down, right_up;
};

namespace mouse {
  // Store information about the mouse button state
  extern mousebuttons_t buttons;

  // Access the position as either coordinates or a 2 dimensional vector
  extern glm::dvec2 position;

  // Register the keyboard input handler with the currently active window
  void init();

  // Reset the `click` and `up` attributes as they should only be set for
  // the duration of one update tick.
  void update();
}  // namespace mouse
