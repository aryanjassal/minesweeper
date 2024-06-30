#pragma once

#include <vector>

#include "texture.hpp"
#include "transform.hpp"
#include "utils/id.hpp"
#include "utils/types.hpp"
#include "vertex.hpp"

class Object {
 public:
  id::id_t id;
  str handle;
  bool active = true;

  std::vector<vert> vertices;
  Transform transform;
  Texture texture;

  void render();

  Object() : id(id::generate()){};
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

// Get a mutable pointer to an object via it's ID, otherwise returns `nullptr`.
Object *get(id::id_t id);

// Get the first instance of an object which has the specified handle, otherwise
// returns `nullptr`.
Object *get(str handle);

// Destroys objects based on the given constraints.
bool destroy(id::id_t id);
bool destroy(Object *object);
bool destroy(const std::vector<Object *> &objects);

// Delete all tracked objects, active or inactive.
void clear();

}  // namespace object_manager

// Alias the namespace to something more convenient.
namespace omg = object_manager;
