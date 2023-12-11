#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <vector>

#include "transform.hpp"
#include "typedefs.hpp"
#include "vertex.hpp"

class Object {
 public:
  u32 id;
  cstr handle;

  std::vector<f32> vertices;

  Object(cstr handle, std::vector<f32> vertices);

  void render();
};

#endif
