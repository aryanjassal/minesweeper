#pragma once
#include <sys/types.h>

#define STB_IMAGE_IMPLEMENTATION

#include <vector>

#include "glad/glad.h"
#include "utils/id.hpp"
#include "utils/types.hpp"

class Texture {
 public:
  id::id_t id;

  u32 ogl_id;
  str handle;
  i32 width, height;

  void bind();

  Texture() : id(id::generate()){};
};

// NOTE: still contains the overhead associated with texture switching.
class TextureMap {
 public:
  std::vector<Texture> textures;
  u8 index;
};

namespace texture_manager {

// Create a new texture with the given parameters.
Texture *create(
    str handle, str file_path, bool transparent = false, i32 filter = GL_LINEAR
);

// Remove a previously-defined texture.
bool destroy(id::id_t id);
bool destroy(str handle);

}  // namespace texture_manager

// Alias the namespace to something more convenient.
namespace txmg = texture_manager;
