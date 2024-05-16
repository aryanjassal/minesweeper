#include "shaders.hpp"

#include <fstream>
#include <map>
#include <sstream>

#include "glad/glad.h"
#include "glm/glm.hpp"  // IWYU pragma: keep
#include "glm/gtc/type_ptr.hpp"
#include "utils/logging.hpp"
#include "utils/types.hpp"

// Hashmap to store all created shaders
std::map<str, Shader> _shaders = std::map<str, Shader>();

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

Shader::Shader(str handle, str _vert, str _frag, str _geom) {
  this->handle = handle;

  if (!_vert.empty()) {
    this->vert = read_file(_vert);
  } else {
    // fallback vertex shader
    this->vert = read_file("src/shaders/pass/pass.vs");
  }

  if (!_frag.empty()) {
    this->frag = read_file(_frag);
  } else {
    // fallback fragment shader
    this->frag = read_file("src/shaders/pass/pass.fs");
  }

  // if (_geom) {
  //   this->geom = read_file(_geom);
  // } else {
  //   // fallback geometry shader
  //   this->geom = read_file("src/shaders/pass/pass.gs");
  // }

  // // This fancy method is needed to insert a new value into the hashmap
  // // without requiring an empty constructor
  // _shaders.insert(std::map<cstr, Shader>::value_type(this->handle, *this));
  
  debug("Created shader: " + handle);
}

void Shader::compile() {
  // Create the vertex shader
  cstr vcode = this->vert.c_str();
  u32 vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vcode, nullptr);
  glCompileShader(vs);
  log_errors(vs, SHADER_VERT);

  // Create the fragment shader
  cstr fcode = this->frag.c_str();
  u32 fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fcode, nullptr);
  glCompileShader(fs);
  log_errors(fs, SHADER_FRAG);

  // // Create the geometry shader
  // cstr gcode = this->geom.c_str();
  // u32 gs = glCreateShader(GL_GEOMETRY_SHADER);
  // glShaderSource(gs, 1, &gcode, nullptr);
  // glCompileShader(gs);
  // log_errors(gs, SHADER_GEOM);

  // Attach the shaders to the OpenGL program
  this->id = glCreateProgram();
  glAttachShader(this->id, vs);
  glAttachShader(this->id, fs);
  // glAttachShader(this->id, gs);
  glLinkProgram(this->id);
  log_errors(this->id, SHADER_PROG);
  debug("Compiled shader: " + this->handle);

  // Delete the shaders as they have already been linked to the shader
  glDeleteShader(vs);
  glDeleteShader(fs);
  // glDeleteShader(gs);
}

void Shader::activate() { glUseProgram(this->id); }

void Shader::set_bool(cstr id, bool val) {
  glUniform1i(glGetUniformLocation(this->id, id), val ? 1 : 0);
}
void Shader::set_f32(cstr id, f32 val) {
  glUniform1f(glGetUniformLocation(this->id, id), val);
}

void Shader::set_i32(cstr id, i32 val) {
  glUniform1i(glGetUniformLocation(this->id, id), val);
}

void Shader::set_vec2(cstr id, f32 x, f32 y) {
  glUniform2f(glGetUniformLocation(this->id, id), x, y);
}

void Shader::set_vec2(cstr id, glm::vec2 val) {
  glUniform2f(glGetUniformLocation(this->id, id), val.x, val.y);
}

void Shader::set_vec3(cstr id, f32 x, f32 y, f32 z) {
  glUniform3f(glGetUniformLocation(this->id, id), x, y, z);
}

void Shader::set_vec3(cstr id, glm::vec3 val) {
  glUniform3f(glGetUniformLocation(this->id, id), val.x, val.y, val.z);
}

void Shader::set_vec4(cstr id, f32 x, f32 y, f32 z, f32 w) {
  glUniform4f(glGetUniformLocation(this->id, id), x, y, z, w);
}

void Shader::set_vec4(cstr id, glm::vec4 val) {
  glUniform4f(glGetUniformLocation(this->id, id), val.x, val.y, val.z, val.w);
}

void Shader::set_mat4(cstr id, const glm::mat4 &val) {
  u32 location = glGetUniformLocation(this->id, id);
  glUniformMatrix4fv(location, 1, false, glm::value_ptr(val));
}

void Shader::log_errors(u32 shader, i8 type) {
  i32 compiled = false;

  char log[512];  // clang-format ignore

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

Shader *Shaders::get(str handle) {
  auto shader = _shaders.find(handle);
  if (shader == _shaders.end()) {
    error("Shader '" + handle + "' doesn't exist");
  }
  return &shader->second;
}
