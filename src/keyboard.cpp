#include "keyboard.hpp"

#include <vector>

#include "utils/logging.hpp"
#include "window.hpp"

std::map<u16, kbkey_t> keys = std::map<u16, kbkey_t>();

// NOTE: all the types need to be i32 as that is what the callback function
// expects.
void callback(GLFWwindow *win, i32 _key, i32 code, i32 act, i32 mods) {
  kbkey_t k = {};

  k.shift = (mods & 1);
  k.ctrl = (mods & 1 << 1);
  k.alt = (mods & 1 << 2);
  k.super = (mods & 1 << 3);
  k.caps = (mods & 1 << 4);
  k.num = (mods & 1 << 5);

  if (_key < 0) return;

  if (act == GLFW_PRESS) {
    k.pressed = true;
    k.down = true;
    k.released = false;
    keys[_key] = k;
  } else if (act == GLFW_RELEASE) {
    k.pressed = false;
    k.down = false;
    k.released = true;
    keys[_key] = k;
  }
}

void kb::init() {
  glfwSetKeyCallback(window, callback);
  debug("Installed keyboard callback");
}

void kb::update() {
  std::vector<u16> rkeys;
  for (auto &k : keys) {
    k.second.pressed = false;
    k.second.released = false;
  }

  for (const auto k : rkeys) {
    keys.erase(keys.find(k));
  }

  for (const auto k : keys) {
    if (!k.second.pressed && !k.second.down && !k.second.released) {
      rkeys.push_back(k.first);
    }
  }
}
