#pragma once

#include <vector>

#include "shaders.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "utils/types.hpp"
#include "vertex.hpp"

class Renderer {
 public:
  // Shader object linked to this renderer. Multiple shaders for a single
  // renderer are currently unsupported.
  Shader shader;

  // Store the handle of the renderer for easier debugging.
  str handle;

  Renderer() = default;

  // Sets the instance as the active renderer
  void activate();

  // Unbinds and disables the VAO.
  // NOT IMPLEMENTED YET
  void unbind();

  // Render image onto the screen given an array of vertices (in
  // GL_TRIANGLE_STRIP layout).
  void render(std::vector<vert> vertices, Transform transform,
              Texture texture = Texture());

  // References to the buffers storing the attributes and vertex data.
  u32 vao, vbo;
};

namespace Renderers {

// Create a new renderer
Renderer *create(str handle, Shader &shader);

// Delete all renderers.
void clear();

}

extern Renderer *active_renderer;
