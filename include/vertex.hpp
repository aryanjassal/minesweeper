#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include "math/vector.hpp"

struct vert {
 public:
  vec3 pos;
  vec2 tex;

  vert(vec3 pos) : pos{pos}, tex{vec2(0)} {}
  vert(vec3 pos, vec2 tex) : pos{pos}, tex{tex} {}
};

#endif
