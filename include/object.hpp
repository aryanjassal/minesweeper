#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <vector>

#include "texture.hpp"
#include "transform.hpp"
#include "utils/types.hpp"
#include "vertex.hpp"

class Object {
 public:
  u32 id;
  cstr handle;

  std::vector<vert> vertices;
  Transform transform;
  Texture texture;

  void render();
};

namespace Objects {

// Create a new object with the given parameters.
Object *create(cstr handle, std::vector<vert> vertices,
               Texture texture = Texture());

// Return a vector of all active objects.
std::vector<Object *> all();

}  // namespace Objects

#endif
