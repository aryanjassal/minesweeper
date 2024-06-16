#include "mouse.hpp"

#include <GLFW/glfw3.h>

#include "utils/logging.hpp"
#include "utils/types.hpp"
#include "window.hpp"

mouse_t Mouse = mouse_t();

void pos_callback(GLFWwindow *win, double x, double y) {
  Mouse.position = glm::vec2(x, y);
  debug("Moved to pos " + std::to_string(x) + " " + std::to_string(y));
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
    Mouse.left_click = is_pressed;
    Mouse.left_down = is_pressed;
    Mouse.left_up = ~is_pressed;
  }

  if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    Mouse.right_click = is_pressed;
    Mouse.right_down = is_pressed;
    Mouse.right_up = ~is_pressed;
  }

  if (is_pressed) {
    debug("Mouse button pressed");
  } else {
    debug("Mouse button released");
  }
}

void mouse_t::init() {
  glfwSetCursorPosCallback(window, pos_callback);
  glfwSetMouseButtonCallback(window, btn_callback);
  debug("Installed mouse callback");
}

void mouse_t::update() {
  Mouse.left_up = false;
  Mouse.left_down = false;
  Mouse.right_up = false;
  Mouse.right_down = false;
}
