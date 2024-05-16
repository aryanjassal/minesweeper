#pragma once

#include "utils/types.hpp"

#define LOGGER_NONE 0
#define LOGGER_FATAL 1
#define LOGGER_ERROR 2
#define LOGGER_WARN 3
#define LOGGER_INFO 4
#define LOGGER_DEBUG 5

void set_loglevel(u32 level);

void debug(str msg);
void info(str msg);
void warn(str msg, bool fail = false);
void error(str msg, bool fail = true);
void fatal(str msg);

// Checks if there was an error in OpenGL, and quits if there was.
// TODO: actually make this good
void gl_geterror();
