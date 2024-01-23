#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <vector>

#include "texture.hpp"
#include "typedefs.hpp"
#include "vertex.hpp"

class Object {
 public:
  u32 id;
  cstr handle;

  std::vector<vert> vertices;
  Texture texture;

  void render();
};

namespace Objects {

Object *create(cstr handle, std::vector<vert> vertices,
               Texture texture = Texture());
std::vector<Object *> all();

}  // namespace Objects

#endif
