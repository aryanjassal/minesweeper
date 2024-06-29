#include "mouse.hpp"

#include <GLFW/glfw3.h>

#include "utils/logging.hpp"
#include "utils/types.hpp"
#include "window.hpp"

glm::dvec2 mouse::position = glm::dvec2(0);
mousebuttons_t mouse::buttons = mousebuttons_t();

void pos_callback(GLFWwindow *win, double x, double y) {
  mouse::position = glm::vec2(x, y);
  debug("Mouse pos: " + std::to_string((int)x) + " " + std::to_string((int)y));
}

// NOTE: all the types need to be i32 as that is what the callback function
// expects.
void btn_callback(GLFWwindow *win, i32 button, i32 is_pressed, i32 mods) {
  // If the button is pressed, then `is_pressed` will be 1. Otherwise it will be
  // 0. We can use this to our advantage and implicitly convert it to a boolean.
  // If the button is pressed, then click and down will be true, and up will be
  // false. Similarly, if the button is released, then click and down will be
  // false, and up will be true.

  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    mouse::buttons.left = is_pressed;
    mouse::buttons.left_down = is_pressed;
    mouse::buttons.left_up = ~is_pressed;
  }

  if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    mouse::buttons.right = is_pressed;
    mouse::buttons.right_down = is_pressed;
    mouse::buttons.right_up = ~is_pressed;
  }

  if (is_pressed) {
    debug("Mouse button pressed");
  } else {
    debug("Mouse button released");
  }
}

void mouse::init() {
  glfwSetCursorPosCallback(window, pos_callback);
  glfwSetMouseButtonCallback(window, btn_callback);
  debug("Installed mouse callback");
}

void mouse::update() {
  mouse::buttons.left_up = false;
  mouse::buttons.left_down = false;
  mouse::buttons.right_up = false;
  mouse::buttons.right_down = false;
}
