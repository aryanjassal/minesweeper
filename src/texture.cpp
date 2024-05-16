#include "texture.hpp"

#include <map>

#include "glad/glad.h"
#include "stb/stb_image.h"
#include "utils/logging.hpp"

// Hashmap to store all the created objects
std::map<str, Texture> all_textures = std::map<str, Texture>();

// Bind texture to "curent texture"
void Texture::bind() { glBindTexture(GL_TEXTURE_2D, this->id); }

// Create a new texture
Texture *Textures::create(
    str handle, str file_path, bool transparent, i32 filter
) {
  if (all_textures.find(handle) != all_textures.end()) {
    error("A texture with handle '" + handle + "' already exists.");
  }

  i32 image_channels = transparent ? GL_RGBA : GL_RGB;

  Texture texture;
  texture.handle = handle;
  glGenTextures(1, &texture.id);

  // Make sure the image is loaded in the correct orientation.
  stbi_set_flip_vertically_on_load(true);

  // Load the image while discarding the number of channels in the image.
  u8 *data =
      stbi_load(file_path.c_str(), &texture.width, &texture.height, nullptr, 4);

  // Check if the image failed to load
  if (!data) {
    str e = "Failed to load image '" + file_path + "'\n";
    cstr reason = stbi_failure_reason();
    error(e + (reason ? reason : ""));
  }

  // Generate the texture
  glBindTexture(GL_TEXTURE_2D, texture.id);
  glTexImage2D(
      GL_TEXTURE_2D, 0, image_channels, texture.width, texture.height, 0,
      image_channels, GL_UNSIGNED_BYTE, data
  );
  glTexImage2D(
      GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA,
      GL_UNSIGNED_BYTE, data
  );
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
  debug("Created new texture: " + handle);
  return &all_textures[handle];
}

void Textures::remove(str handle) {
  // Confirm that the texture exists in the hashmap
  if (all_textures.find(handle) == all_textures.end()) return;

  // Delete the buffer and then delete the reference from the hashmap to ensure
  // no dangling references and a clean removal of the texture.
  glDeleteTextures(1, &all_textures[handle].id);
  all_textures.erase(handle);

  debug("Deleted texture: " + handle);
}
