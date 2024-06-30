#pragma once

#include <vector>

#include "shaders.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "utils/id.hpp"
#include "utils/types.hpp"
#include "vertex.hpp"

#define RENDER_POLYGON 0
#define RENDER_WIREFRAME 1

class Renderer {
 public:
  id::id_t id;
  str handle;

  // References to the buffers storing the attributes and vertex data.
  u32 vao, vbo;

  // Shader object linked to this renderer. Multiple shaders for a single
  // renderer are currently unsupported.
  Shader shader;


  // Sets the instance as the active renderer
  void activate();

  // Unbinds and disables the VAO.
  // WARN: NOT IMPLEMENTED YET
  void unbind();

  // Render image onto the screen given an array of vertices (in
  // GL_TRIANGLE_STRIP layout).
  void render(
      std::vector<vert> vertices, Transform transform,
      Texture texture = Texture()
  );

  Renderer() : id(id::generate()){};
};

namespace renderer_manager {

// Create a new renderer
Renderer *create(str handle, Shader &shader, u8 mode = RENDER_POLYGON);

// Get a renderer
Renderer *get(id::id_t id);
Renderer *get(str handle);

// Destroys renderers based on the given constraints.
bool destroy(id::id_t id);

// Delete all renderers.
void clear();

}  // namespace renderer_manager

// Store the active renderer which will be used to render any mesh to the
// screen.
extern Renderer *active_renderer;

// Alias the namespace to something more convenient.
namespace rmg = renderer_manager;
