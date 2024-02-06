#include "object.hpp"

#include "renderer.hpp"

// Vector to store all the created objects
std::vector<Object> all_objects = std::vector<Object>();

// Keep track of the next id for an instantiated object
u32 next_id = 0;

Object *Objects::create(cstr handle, std::vector<vert> vertices,
                        Texture texture) {
  Object obj;
  obj.handle = handle;
  obj.vertices = vertices;
  obj.id = next_id++;
  obj.texture = texture;
  all_objects.push_back(obj);

  return &all_objects[obj.id];
}

std::vector<Object *> Objects::all() {
  std::vector<Object *> out;
  // Need this loop to convert vector of objects into a vector pointing back to
  // the original data container. Note this is SUPER TEMP
  for (auto &obj : all_objects) {
    out.push_back(&obj);
  }
  return out;
}

void Object::render() {
  active_renderer->render(this->vertices, this->texture);
}
