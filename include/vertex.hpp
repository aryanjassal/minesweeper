#pragma once

#include "glm/glm.hpp"  // IWYU pragma: keep

struct vert {
 public:
  glm::vec3 pos;
  glm::vec2 tex;

  vert(glm::vec3 pos) : pos{pos}, tex{glm::vec2(0)} {}
  vert(glm::vec3 pos, glm::vec2 tex) : pos{pos}, tex{tex} {}
};
