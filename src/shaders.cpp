#include "shaders.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "glad/glad.h"
#include "typedefs.hpp"
#include "utils.hpp"

// Hashmap to store all created shaders
std::map<cstr, Shader> _shaders = std::map<cstr, Shader>();

// Reads a file at the location `path` and returns the contents as a string
str read_file(cstr path) {
  std::ifstream f(path);
  if (!f.is_open()) {
    str msg = "Failed to open '";
    msg += path;
    msg += "'";
    error(msg);
  }
  std::stringstream out;
  out << f.rdbuf();
  f.close();
  return out.str();
}

Shader::Shader(cstr handle, cstr _vert, cstr _frag, cstr _geom) {
  this->handle = handle;

  if (_vert) {
    // error("we shouldn't be here.");
    this->vert = read_file(_vert);
  } else {
    // fallback vertex shader
    this->vert = read_file("src/shaders/pass/pass.vs");
  }

  if (_frag) {
    // error("we shouldn't be here.");
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
  // without
  // // requiring an empty constructor
  // _shaders.insert(std::map<cstr, Shader>::value_type(this->handle, *this));
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

  // Delete the shaders as they have already been linked to the shader
  glDeleteShader(vs);
  glDeleteShader(fs);
  // glDeleteShader(gs);
}

void Shader::activate() { glUseProgram(this->id); }

// TODO(aryanj): properly implement this
// void Shader::configure_attributes(i32 _layout_num,
//                                   std::vector<i32> _layout_size) {
//   if (this->layout_num) {
//     error("Shader attributes have alrealy been configured");
//   }
//
//   if (!_layout_num || !_layout_size.size()) {
//     error("Invalid values for shader attributes");
//   }
//
//   if (this->layout_num != this->layout_size.size()) {
//     error("`layout_num` must be equal to the size of `layout_size`");
//   }
//
//   this->layout_num = _layout_num;
//   this->layout_size = _layout_size;
// }

// void Shader::configure_vao() {
//   if (!this->layout_num) {
//     error("Shader attributes must be set before calling this method");
//   }
//
//   const auto size = sizeof(f32);
//
//   // TODO(aryanj): stride doent get proper value. what i need is to calculate
//   // the sum of the layout_size before multiplying standard size with it to get
//   // the stride.
//
//   //  u32 sum_size = 0;
//   //  for (u32 i = 0; i < this->layout_num; ++i) {
//   //    glVertexAttribPointer(i, this->layout_size[i], GL_FLOAT, GL_FALSE,
//   //                          this->layout_size[i] * size,
//   //                          (void *)(sum_size * size));
//   //    sum_size += this->layout_size[i];
//   //    glEnableVertexAttribArray(i);
//   //  }
//
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void *)0);
//   glEnableVertexAttribArray(0);
// }

void Shader::set_bool(cstr id, bool val) {
  glUniform1i(glGetUniformLocation(this->id, id), val ? 1 : 0);
}
void Shader::set_f32(cstr id, f32 val) {
  glUniform1f(glGetUniformLocation(this->id, id), val);
}

void Shader::set_i32(cstr id, i32 val) {
  glUniform1i(glGetUniformLocation(this->id, id), val);
}

void Shader::set_v2(cstr id, f32 x, f32 y) {
  glUniform2f(glGetUniformLocation(this->id, id), x, y);
}

void Shader::set_v2(cstr id, v2 val) {
  glUniform2f(glGetUniformLocation(this->id, id), val.x, val.y);
}

void Shader::set_v3(cstr id, f32 x, f32 y, f32 z) {
  glUniform3f(glGetUniformLocation(this->id, id), x, y, z);
}

void Shader::set_v3(cstr id, v3 val) {
  glUniform3f(glGetUniformLocation(this->id, id), val.x, val.y, val.z);
}

void Shader::set_v4(cstr id, f32 x, f32 y, f32 z, f32 w) {
  glUniform4f(glGetUniformLocation(this->id, id), x, y, z, w);
}

void Shader::set_v4(cstr id, v4 val) {
  glUniform4f(glGetUniformLocation(this->id, id), val.x, val.y, val.z, val.w);
}

void Shader::set_m4(cstr id, m4 val) {
  glUniformMatrix4fv(glGetUniformLocation(this->id, id), 1, false, &val.data());
}

void Shader::log_errors(u32 shader, i8 type) {
  i32 compiled = false;

  char log[512];

  // std::array<char, 1024> info_log;
  if (type) {
    cstr s;
    switch (type) {
      case SHADER_VERT:
        s = "SHADER_VERT";
        break;
      case SHADER_FRAG:
        s = "SHADER_FRAG";
        break;
      case SHADER_GEOM:
        s = "SHADER_GEOM";
        break;
      default:
        s = "SHADER_UNKNOWN";
        break;
    }

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
      glGetShaderInfoLog(shader, 512, nullptr, log);
      std::cout << "[ERROR] Shader '" << this->handle << "' could not compile "
                << s << std::endl;
      std::cout << log << std::endl;
      exit(-1);
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &compiled);
    if (!compiled) {
      glGetProgramInfoLog(shader, 512, nullptr, log);
      std::cout << "[ERROR] Shader program '" << this->handle
                << "' failed to compile." << std::endl;
      std::cout << log << std::endl;
      exit(-1);
    }
  }
}

Shader *Shaders::get(cstr handle) {
  auto shader = _shaders.find(handle);
  if (shader == _shaders.end()) {
    str msg = "Shader '";
    msg += handle;
    msg += "' doesn't exist";
    error(msg);
  }
  return &shader->second;
}
