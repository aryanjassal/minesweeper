#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include "glfw/glfw3.h"
#include "glm/glm.hpp"  // IWYU pragma: keep
#include "utils/types.hpp"

extern GLFWwindow* window;

namespace win {

void init(cstr title, u32 width, u32 height);
void init(cstr title, glm::vec2 dimensions);

}  // namespace win

#endif
