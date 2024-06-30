#include "shaders.hpp"

#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include "glm/glm.hpp"  // IWYU pragma: keep
#include "glm/gtc/type_ptr.hpp"
#include "utils/logging.hpp"
#include "utils/types.hpp"

// Hashmap to store all created shaders
std::vector<Shader> all_shaders = std::vector<Shader>();

// Reads a file at the location `path` and returns the contents as a string
str read_file(str path) {
  std::ifstream f(path);
  if (!f.is_open()) {
    error("Failed to open '" + path + "'");
  }
  std::stringstream out;
  out << f.rdbuf();
  f.close();
  return out.str();
}

Shader *shader_manager::create(str handle, str _vert, str _frag, str _geom) {
  Shader shader;
  shader.handle = handle;

  if (!_vert.empty()) {
    shader.vert = read_file(_vert);
  } else {
    error("Vertex shader must be provided");
  }

  if (!_frag.empty()) {
    shader.frag = read_file(_frag);
  } else {
    error("Fragment shader must be provided");
  }

  if (!_geom.empty()) {
    shader.geom = read_file(_geom);
  } else {
    shader.geom = "";
  }

  all_shaders.push_back(shader);
  debug("Created shader: " + handle);
  return &all_shaders.back();
}

void Shader::compile() {
  // Create a shader program to link everything to.
  this->ogl_id = glCreateProgram();
  u32 vs = glCreateShader(GL_VERTEX_SHADER);
  u32 fs = glCreateShader(GL_FRAGMENT_SHADER);
  u32 gs = glCreateShader(GL_GEOMETRY_SHADER);

  // Create and link the vertex shader.
  cstr vcode = this->vert.c_str();
  glShaderSource(vs, 1, &vcode, nullptr);
  glCompileShader(vs);
  log_errors(vs, SHADER_VERT);
  glAttachShader(this->ogl_id, vs);

  // Create and link the fragment shader.
  cstr fcode = this->frag.c_str();
  glShaderSource(fs, 1, &fcode, nullptr);
  glCompileShader(fs);
  log_errors(fs, SHADER_FRAG);
  glAttachShader(this->ogl_id, fs);

  // Create and link the geometry shader.
  if (!this->geom.empty()) {
    cstr gcode = this->geom.c_str();
    glShaderSource(gs, 1, &gcode, nullptr);
    glCompileShader(gs);
    log_errors(gs, SHADER_GEOM);
    glAttachShader(this->ogl_id, gs);
  }

  glLinkProgram(this->ogl_id);
  log_errors(this->ogl_id, SHADER_PROG);
  debug("Compiled shader: " + this->handle);

  // Delete the shaders as they have already been linked to the shader
  glDeleteShader(vs);
  glDeleteShader(fs);
  if (!this->geom.empty()) glDeleteShader(gs);
}

void Shader::activate() {
  glUseProgram(this->ogl_id);
  debug("Activated shader: " + this->handle);
}

void Shader::set_bool(cstr id, bool val) {
  glUniform1i(glGetUniformLocation(this->ogl_id, id), val ? 1 : 0);
}
void Shader::set_f32(cstr id, f32 val) {
  glUniform1f(glGetUniformLocation(this->ogl_id, id), val);
}

void Shader::set_i32(cstr id, i32 val) {
  glUniform1i(glGetUniformLocation(this->ogl_id, id), val);
}

void Shader::set_vec2(cstr id, f32 x, f32 y) {
  glUniform2f(glGetUniformLocation(this->ogl_id, id), x, y);
}

void Shader::set_vec2(cstr id, glm::vec2 val) {
  glUniform2f(glGetUniformLocation(this->ogl_id, id), val.x, val.y);
}

void Shader::set_vec3(cstr id, f32 x, f32 y, f32 z) {
  glUniform3f(glGetUniformLocation(this->ogl_id, id), x, y, z);
}

void Shader::set_vec3(cstr id, glm::vec3 val) {
  glUniform3f(glGetUniformLocation(this->ogl_id, id), val.x, val.y, val.z);
}

void Shader::set_vec4(cstr id, f32 x, f32 y, f32 z, f32 w) {
  glUniform4f(glGetUniformLocation(this->ogl_id, id), x, y, z, w);
}

void Shader::set_vec4(cstr id, glm::vec4 val) {
  glUniform4f(
      glGetUniformLocation(this->ogl_id, id), val.x, val.y, val.z, val.w
  );
}

void Shader::set_mat4(cstr id, const glm::mat4 &val) {
  u32 location = glGetUniformLocation(this->ogl_id, id);
  glUniformMatrix4fv(location, 1, false, glm::value_ptr(val));
}

void Shader::log_errors(u32 shader, i8 type) {
  i32 compiled = false;

  char log[512];

  if (type) {
    cstr shader_type;
    switch (type) {
      case SHADER_VERT:
        shader_type = "SHADER_VERT";
        break;
      case SHADER_FRAG:
        shader_type = "SHADER_FRAG";
        break;
      case SHADER_GEOM:
        shader_type = "SHADER_GEOM";
        break;
      default:
        shader_type = "SHADER_UNKNOWN";
        break;
    }

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
      glGetShaderInfoLog(shader, 512, nullptr, log);
      error(
          "Shader '" + this->handle + "' could not compile " + shader_type +
          "\n" + log
      );
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &compiled);
    if (!compiled) {
      glGetProgramInfoLog(shader, 512, nullptr, log);
      error("Shader program '" + this->handle + "' failed to compile.\n" + log);
    }
  }
}

Shader *shader_manager::get(id::id_t id) {
  for (auto &shader : all_shaders) {
    if (shader.id == id) return &shader;
  }
  return nullptr;
}

Shader *shader_manager::get(str handle) {
  for (auto &shader : all_shaders) {
    if (shader.handle == handle) return &shader;
  }
  return nullptr;
}
