#pragma once

#include "glm/glm.hpp"  // IWYU pragma: keep

// Register a mouse object storing the current state of the mouse and its
// buttons
class mouse_t {
 public:
  // Store information about the mouse button state
  bool left_click, left_down, left_up;
  bool right_click, right_down, right_up;

  // Access the position as either coordinates or a 2 dimensional vector
  union {
    glm::dvec2 position;
    double x, y;
  };

  // Register the keyboard input handler with the currently active window
  void init();

  // Reset the `click` and `up` attributes as they should only be set for
  // the duration of one update tick.
  void update();
};

extern mouse_t Mouse;
