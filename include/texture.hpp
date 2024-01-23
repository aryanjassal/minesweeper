#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

#include <vector>

#include "typedefs.hpp"

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

Texture *create(cstr handle, cstr file_path, bool transparent = false);

}

#endif
