#include "texture.hpp"

#include <map>

#include "glad/glad.h"
#include "stb/stb_image.h"
#include "utils/logging.hpp"

// Hashmap to store all the created objects
std::map<cstr, Texture> all_textures = std::map<cstr, Texture>();

// Bind texture to "curent texture"
void Texture::bind() { glBindTexture(GL_TEXTURE_2D, this->id); }

// Create a new texture
Texture *Textures::create(cstr handle, cstr file_path, bool transparent,
                          i32 filter) {
  if (all_textures.find(handle) != all_textures.end()) {
    str s;
    error(s + "A texture with handle '" + handle + "' already exists.");
  }

  i32 image_channels = transparent ? GL_RGBA : GL_RGB;

  Texture texture;
  texture.handle = handle;
  glGenTextures(1, &texture.id);

  // Discarding the value of the number of channels
  u8 *data = stbi_load(file_path, &texture.width, &texture.height, nullptr, 4);

  // Check if the image failed to load
  if (!data) {
    str e;
    e = e + "Failed to load image '" + file_path + "'\n";
    cstr reason = stbi_failure_reason();
    if (reason) {
      e += reason;
    }
    error(e);
  }

  // Generate the texture
  glBindTexture(GL_TEXTURE_2D, texture.id);
  glTexImage2D(GL_TEXTURE_2D, 0, image_channels, texture.width, texture.height,
               0, image_channels, GL_UNSIGNED_BYTE, data);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, data);
  stbi_image_free(data);

  // Set texture wrap and filter settings.
  // NOTE: Through trial and error I have realised that this is critical.
  // Otherwise the code will not work.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

  glBindTexture(GL_TEXTURE_2D, 0);

  // Save the texture in the texture hashmap
  all_textures[handle] = texture;
  return &all_textures[handle];
}

// void Texture::remove(cstr handle) {
//
// }
