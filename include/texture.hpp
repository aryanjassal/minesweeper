#pragma once

#include <vector>

#include "glad/glad.h"
#include "utils/types.hpp"

class Texture {
 public:
  u32 id;
  cstr handle;
  i32 width, height;

  void bind();

  // private:
  //  u32 texture_format_;
};

// Note: still contains the overhead associated with texture switching.
class TextureMap {
 public:
  std::vector<Texture> textures;
  u8 index;
};

namespace Textures {

Texture *create(cstr handle, cstr file_path, bool transparent = false,
                i32 filter = GL_LINEAR);

}
