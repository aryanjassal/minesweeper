#include "object.hpp"

#include <algorithm>

#include "renderer.hpp"
#include "utils/logging.hpp"

// Default object
Object default_object;

// Vector to store all the created objects
std::vector<Object> all_objects = std::vector<Object>();

// Keep track of the next id for an instantiated object
u32 next_id = 0;

Object &Objects::create(
    str handle, std::vector<vert> vertices, Texture texture, Transform transform
) {
  auto it = std::find_if(
      all_objects.begin(), all_objects.end(),
      [&](const auto &obj) { return obj.handle == handle; }
  );
  if (it != all_objects.end()) {
    warn("An object with handle '" + handle + "' already exists");
    return default_object;
  }

  Object obj;
  obj.handle = handle;
  obj.vertices = vertices;
  obj.id = next_id++;
  obj.texture = texture;
  obj.transform = transform;
  all_objects.push_back(obj);

  debug("Created new object: " + handle);
  return all_objects[obj.id];
}

std::vector<Object> Objects::all() {
  std::vector<Object> out;
  // Need this loop to convert vector of objects into a vector pointing back to
  // the original data container. Note this is SUPER TEMP
  for (auto obj : all_objects) {
    out.push_back(obj);
  }
  return out;
}

void Object::render() {
  active_renderer.render(this->vertices, this->transform, this->texture);
}
