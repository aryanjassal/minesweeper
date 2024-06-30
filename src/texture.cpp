#include "texture.hpp"
#include <algorithm>

#include "glad/glad.h"
#include "stb/stb_image.h"
#include "utils/id.hpp"
#include "utils/logging.hpp"

// Hashmap to store all the created objects
std::vector<Texture> all_textures = std::vector<Texture>();

// Bind texture to "curent texture"
void Texture::bind() { 
  glBindTexture(GL_TEXTURE_2D, this->ogl_id); 
  debug("Activated texture: " + handle, LOGLEVEL_DEBUG_MORE);
}

// Create a new texture
Texture *texture_manager::create(
    str handle, str file_path, bool transparent, i32 filter
) {
  i32 image_channels = transparent ? GL_RGBA : GL_RGB;

  Texture texture;
  texture.handle = handle;
  glGenTextures(1, &texture.ogl_id);

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
  glBindTexture(GL_TEXTURE_2D, texture.ogl_id);
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
  // Through trial and error I have realised that this is critical.
  // Otherwise the code will not work.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

  glBindTexture(GL_TEXTURE_2D, 0);

  // Save the texture in the texture hashmap
  all_textures.push_back(texture);
  debug("Created new texture: " + handle);
  return &all_textures.back();
}

bool texture_manager::destroy(id::id_t id) {
  // Create an iterator which would only contain objects whose ID is
  // similar to the argument.
  auto it = std::find_if(
      all_textures.begin(), all_textures.end(),
      [&](const Texture &tex) { return tex.id == id; }
  );

  if (it == all_textures.end()) return false;

  Texture &tex = *it;

  // Delete the buffer and then delete the reference from the hashmap to ensure
  // no dangling references and a clean removal of the texture.
  glDeleteTextures(1, &tex.ogl_id);
  debug("Deleted texture: " + tex.handle);

  // If the object exists in the array, then erase it. Otherwise, return
  // `false`, signifying something went wrong.
  if (it != all_textures.end()) {
    all_textures.erase(it);
    return true;
  }
  return false;
}

bool texture_manager::destroy(str handle) {
  // Create an iterator which would only contain objects whose ID is
  // similar to the argument.
  auto it = std::find_if(
      all_textures.begin(), all_textures.end(),
      [&](const Texture &tex) { return tex.handle == handle; }
  );

  if (it == all_textures.end()) return false;

  Texture &tex = *it;

  // Delete the buffer and then delete the reference from the hashmap to ensure
  // no dangling references and a clean removal of the texture.
  glDeleteTextures(1, &tex.ogl_id);
  debug("Deleted texture: " + handle);

  // If the object exists in the array, then erase it. Otherwise, return
  // `false`, signifying something went wrong.
  if (it != all_textures.end()) {
    all_textures.erase(it);
    return true;
  }
  return false;
}
