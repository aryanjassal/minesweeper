#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include <vector>

#include "glad/glad.h"
#include "utils/types.hpp"

class Texture {
 public:
  u32 id;
  str handle;
  i32 width, height;

  void bind();
};

// NOTE: still contains the overhead associated with texture switching.
class TextureMap {
 public:
  std::vector<Texture> textures;
  u8 index;
};

namespace Textures {

// Create a new texture with the given parameters.
Texture *create(
    str handle, str file_path, bool transparent = false, i32 filter = GL_LINEAR
);

// Remove a previously-defined texture.
void remove(str handle);

}  // namespace Textures
