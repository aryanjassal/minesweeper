#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include "glm/glm.hpp"

struct vert {
 public:
  glm::vec3 pos;
  glm::vec2 tex;

  vert(glm::vec3 pos) : pos{pos}, tex{glm::vec2(0)} {}
  vert(glm::vec3 pos, glm::vec2 tex) : pos{pos}, tex{tex} {}
};

#endif
