#pragma once

#include "utils/types.hpp"

#define LOGLEVEL_NONE 0
#define LOGLEVEL_FATAL 1
#define LOGLEVEL_ERROR 2
#define LOGLEVEL_WARN 3
#define LOGLEVEL_INFO 4
#define LOGLEVEL_DEBUG 5
#define LOGLEVEL_DEBUG_MORE 6

void debug(str msg, u8 debug_level = LOGLEVEL_DEBUG);
void info(str msg);
void warn(str msg, bool fail = false);
void error(str msg, bool fail = true);
void fatal(str msg);

// Checks if there was an error in OpenGL, and quits if there was.
void check_gl_errors();

namespace logging {

// Set the logging level to output
void set_loglevel(u8 level);

}  // namespace logging
