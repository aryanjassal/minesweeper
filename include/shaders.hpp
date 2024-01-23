#ifndef __SHADERS_HPP__
#define __SHADERS_HPP__

#include <vector>

#include "glm/glm.hpp"
#include "typedefs.hpp"

#define SHADER_PROG 0
#define SHADER_VERT 1
#define SHADER_FRAG 2
#define SHADER_GEOM 3

class Shader {
 public:
  // OpenGL identifier for the shader
  u32 id;

  // User-friendly identifier for the shader
  cstr handle;

  // Compiles the shader from the file locations, checking for errors and
  // finally making the shader usable.
  void compile();

  // Creates a shader using the file locations of each file. Default parameter
  // is `nullptr` which would result in a simple passthrough shader. Note that
  // no compilation or error checking is done in this step. Before activating
  // the shader, `compile()` must be called.
  Shader(cstr handle, cstr vert = nullptr, cstr frag = nullptr,
         cstr geom = nullptr);
  Shader() = default;

  // Uses this shader for rendering. Note that this must be called to use the
  // shader for rendering.
  void activate();

  // Modify a uniform in the shader
  void set_bool(cstr id, bool val);
  void set_f32(cstr id, f32 val);
  void set_i32(cstr id, i32 val);
  void set_vec2(cstr id, f32 x, f32 y);
  void set_vec2(cstr id, glm::vec2 val);
  void set_vec3(cstr id, f32 x, f32 y, f32 z);
  void set_vec3(cstr id, glm::vec3 val);
  void set_vec4(cstr id, f32 x, f32 y, f32 z, f32 w);
  void set_vec4(cstr id, glm::vec4 val);
  void set_mat4(cstr id, glm::mat4 val);

 private:
  // Stores the shader code in their respective variables
  str vert, frag, geom;

  // Stores the shader configuration information
  i32 layout_num = 0;
  std::vector<i32> layout_size = std::vector<i32>();

  // Logs any errors while compiling the shaders
  void log_errors(u32 shader, i8 type);
};

namespace Shaders {

Shader *get(cstr handle);

}  // namespace Shaders

#endif
