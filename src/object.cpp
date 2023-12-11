#include "object.hpp"
#include <map>

#include "renderer.hpp"
#include "typedefs.hpp"
#include "vertex.hpp"

// Hashmap to store all the created objects
std::map<u32, Object> _objects = std::map<u32, Object>();

// // Keep track of the next id for an instantiated object
// u32 next_id = 0;

Object::Object(cstr handle, std::vector<f32> vertices) {
  this->handle = handle;
  this->vertices = vertices;
  // this->indices = indices;
  // this->id = next_id++;

  // _objects.insert(std::map<u32, Object>::value_type(this->id, *this));
}

void Object::render() {
  active_renderer->render(this->vertices);
}
