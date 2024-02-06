#include "utils/logging.hpp"

#include <iostream>
#include <stdexcept>

#include "glad/glad.h"

void print(str prefix, str msg, bool fail = false) {
  if (fail) {
    throw std::runtime_error(msg);
  } else {
    std::cout << prefix << " " << msg << std::endl;
  }
}

void info(str msg, bool fail) { print("[INFO]", msg, fail); }
void warn(str msg, bool fail) { print("[WARN]", msg, fail); }
void error(str msg, bool fail) { print("[ERROR]", msg, fail); }

void gl_geterror() {
  u32 err = glGetError();
  if (err) {
    cstr errstr;
    switch (err) {
      case GL_INVALID_ENUM:
        errstr = "INVALID_ENUM";
        break;
      case GL_INVALID_VALUE:
        errstr = "INVALID_VALUE";
        break;
      case GL_INVALID_OPERATION:
        errstr = "INVALID_OPERATION";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        errstr = "INVALID_FRAMEBUFFER_OPERATION";
        break;
      case GL_OUT_OF_MEMORY:
        errstr = "OUT_OF_MEMORY";
        break;
      default:
        errstr = "UNKNOWN_ERROR";
        break;
    }
    std::cout << "GLerror: " << errstr << " (" << err << ")" << std::endl;
    exit(err);
  }
}
