#include "keyboard.hpp"

#include <vector>

#include "utils/logging.hpp"
#include "window.hpp"

std::map<u16, key> keys = std::map<u16, key>();

void domod(key *k, i8 mods) {
  k->shift = (mods & 1);
  k->ctrl = (mods & 1 << 1);
  k->alt = (mods & 1 << 2);
  k->super = (mods & 1 << 3);
  k->caps = (mods & 1 << 4);
  k->num = (mods & 1 << 5);
}

void callback(GLFWwindow *win, int _key, int code, int act, int mods) {
  key k = {};
  domod(&k, mods);

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

void kb::refresh() {
  for (auto &k : keys) {
    k.second.pressed = false;
    k.second.released = false;
  }
}

void kb::clean() {
  std::vector<u16> rkeys;
  for (const auto k : keys) {
    if (!k.second.pressed && !k.second.down && !k.second.released) {
      rkeys.push_back(k.first);
    }
  }

  for (const auto k : rkeys) {
    keys.erase(keys.find(k));
  }
}

void kb::update() {
  kb::refresh();
  kb::clean();
}
