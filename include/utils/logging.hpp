#pragma once

#include "utils/types.hpp"

#define LOGGING_NONE 0
#define LOGGING_FATAL 1
#define LOGGING_ERROR 2
#define LOGGING_WARN 3
#define LOGGING_INFO 4
#define LOGGING_DEBUG 5


void debug(str msg);
void info(str msg);
void warn(str msg, bool fail = false);
void error(str msg, bool fail = true);
void fatal(str msg);

// Checks if there was an error in OpenGL, and quits if there was.
// TODO: actually make this good
void gl_geterror();

namespace Logging {

// Set the logging level to output
void set_loglevel(u32 level);

}
