#pragma once

#include <vector>

#include "utils/types.hpp"
#include "vertex.hpp"

// Note that all values should be clamped between 0 and 1, then scaled
// using the transform.scale attribute for maximum control and
// intuitivity.
// clang-format off
const std::vector<vert> SQUARE_VERTICES = {
  vert(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
  vert(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
  vert(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
  vert(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f))
};
// clang-format on

class Game {
 public:
  u32 max_fps;
  u32 screen_width, screen_height;
  str title;

  virtual void pre_init();
  virtual void init();
  virtual void post_init();

  virtual void pre_render();
  virtual void render();
  virtual void post_render();

  virtual void pre_update();
  virtual void update();
  virtual void post_update();

  void run();

  Game(str title, u32 screen_width, u32 screen_height);
  Game(str title, glm::uvec2 screen_dimensions);
  ~Game();
};
