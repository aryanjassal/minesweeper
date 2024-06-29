#include "object.hpp"

#include <algorithm>

#include "renderer.hpp"
#include "utils/logging.hpp"

// Vector to store all the created objects
std::vector<Object> all_objects = std::vector<Object>();

// Keep track of the next id for an instantiated object
u32 next_id = 0;

Object *object_manager::create(
    str handle, std::vector<vert> vertices, Texture texture, Transform transform
) {
  Object obj;
  obj.handle = handle;
  obj.vertices = vertices;
  obj.id = next_id++;
  obj.texture = texture;
  obj.transform = transform;
  all_objects.push_back(obj);

  debug("Created new object: " + handle);
  return &all_objects[obj.id];
}

std::vector<Object *> object_manager::all() {
  std::vector<Object *> out;
  for (auto &obj : all_objects) {
    if (obj.active) out.push_back(&obj);
  }
  return out;
}

std::vector<Object *> object_manager::find(str handle) {
  std::vector<Object *> out;
  for (auto &obj : all_objects) {
    if (obj.handle == handle) out.push_back(&obj);
  }
  return out;
}

Object *object_manager::get(u32 id) { return &all_objects[id]; }

Object *object_manager::get(str handle) {
  for (auto &obj : all_objects) {
    if (obj.handle == handle) return &obj;
  }
  return nullptr;
}

bool object_manager::destroy(u32 id) {
  // Create an iterator which would only contain objects whose ID is
  // similar to the argument.
  auto it = std::find_if(
      all_objects.begin(), all_objects.end(),
      [&](const Object &obj) { return obj.id == id; }
  );

  // If the object exists in the array, then erase it. Otherwise, return
  // `false`, signifying something went wrong.
  if (it != all_objects.end()) {
    all_objects.erase(it);
    return true;
  }
  return false;
}

bool object_manager::destroy(Object *object) {
  // Create an iterator which would only contain objects whose signature is
  // similar to the argument.
  auto it = std::find_if(
      all_objects.begin(), all_objects.end(),
      [&](const Object &obj) { return &obj == object; }
  );

  // If the object exists in the array, then erase it. Otherwise, return
  // `false`, signifying something went wrong.
  if (it != all_objects.end()) {
    all_objects.erase(it);
    return true;
  }
  return false;
}

bool object_manager::destroy(const std::vector<Object *> &objects) {
  bool destroyed_any = false;
  for (auto obj : objects) {
    destroyed_any = object_manager::destroy(obj) || destroyed_any;
  }
  return destroyed_any;
}

void object_manager::clear() {
  all_objects.clear();
  debug("Cleared all tracked objects");
}

void Object::render() {
  active_renderer.render(this->vertices, this->transform, this->texture);
}
