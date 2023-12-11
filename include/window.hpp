#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "glfw/glfw3.h"

extern GLFWwindow* window;

namespace win {

void init(const char* title);

}  // namespace win

#endif
