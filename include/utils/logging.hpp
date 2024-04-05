#pragma once

#include "utils/types.hpp"

void info(str msg, bool fail = false);
void warn(str msg, bool fail = false);
void error(str msg, bool fail = true);

// Checks if there was an error in OpenGL, and quits if there was.
// TODO actually make this good
void gl_geterror();
