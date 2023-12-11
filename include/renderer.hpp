#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <vector>

#include "shaders.hpp"
#include "transform.hpp"
#include "typedefs.hpp"
#include "vertex.hpp"

class Renderer {
 public:
  Shader shader;

  Renderer(Shader &shader);
  ~Renderer();

  // Sets the instance as the active renderer
  void activate();

  // Render image onto the screen given an array of vertices (in
  // GL_TRIANGLE_STRIP layout).
  void render(std::vector<f32> vertices);

 private:
  u32 vao, vbo;
};

extern Renderer *active_renderer;

#endif
