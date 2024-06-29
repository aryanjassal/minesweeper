#pragma once

#include <vector>

#include "texture.hpp"
#include "transform.hpp"
#include "utils/types.hpp"
#include "vertex.hpp"

// TODO: make the id read-only and immutable
class Object {
 public:
  u32 id;
  str handle;
  bool active = true;

  std::vector<vert> vertices;
  Transform transform;
  Texture texture;

  void render();
};

namespace object_manager {

// Create a new object with the given parameters.
Object *create(
    str handle, std::vector<vert> vertices, Texture texture = Texture(),
    Transform transform = Transform()
);

// Get a mutable vector of all active objects.
std::vector<Object *> all();

// Get a mutable list of all objects which have a matching handle.
std::vector<Object *> find(str handle);

// Get a mutable reference to an object via it's ID.
Object *get(u32 id);

// Get the first instance of an object which has the specified handle, otherwise
// returns `nullptr`.
Object *get(str handle);

// Destroys objects based on the given constraints.
bool destroy(u32 id);
bool destroy(Object *object);
bool destroy(const std::vector<Object *> &objects);

// Delete all tracked objects, active or inactive.
void clear();

}  // namespace object_manager

// Create an easier-to-use alias for object_manager.
namespace om = object_manager;
