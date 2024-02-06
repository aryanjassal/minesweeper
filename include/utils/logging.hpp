#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "utils/types.hpp"

void info(str msg, bool fail = false);
void warn(str msg, bool fail = false);
void error(str msg, bool fail = true);

// Checks if there was an error in OpenGL, and quits if there was.
// TODO(aryanj): actually make this good
void gl_geterror();

#endif
