#include "utils/logging.hpp"

#include <iostream>

#include "glad/glad.h"

u8 loglevel = LOGLEVEL_DEBUG;

void print(str prefix, str msg, bool fail = false) {
  std::cout << prefix << " " << msg << std::endl;
  if (fail) exit(0);
}

void logging::set_loglevel(u8 level) { loglevel = level; }

void debug(str msg) {
  if (loglevel < LOGLEVEL_DEBUG) return;
  print("\033[1;90m DEBUG \033[0m", msg, false);
}

void info(str msg) {
  if (loglevel < LOGLEVEL_INFO) return;
  print("\033[1;36m INFO  \033[0m", msg, false);
}

void warn(str msg, bool fail) {
  if (loglevel < LOGLEVEL_WARN) return;
  print("\033[1;33m WARN  \033[0m", msg, fail);
}

void error(str msg, bool fail) {
  if (loglevel < LOGLEVEL_ERROR) return;
  print("\033[1;31m ERROR \033[0m", msg, fail);
}

void fatal(str msg) {
  if (loglevel < LOGLEVEL_FATAL) return;
  print("\033[1;31m FATAL \033[0m", msg, true);
}

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
    std::cout << "GL_ERR: " << errstr << " (" << err << ")" << std::endl;
    exit(err);
  }
}
