#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <array>
#include <vector>

#include "typedefs.hpp"
#include "vector.hpp"

struct vert {
 public:
  v3 pos;
  v3 norm;
  v2 tex;

  vert(v3 pos) : pos{pos}, norm{v3(0)}, tex{v2(0)} {}
  vert(v3 pos, v3 norm) : pos{pos}, norm{norm}, tex{v2(0)} {}
  vert(v3 pos, v3 norm, v2 tex) : pos{pos}, norm{norm}, tex{tex} {}
};

#endif
