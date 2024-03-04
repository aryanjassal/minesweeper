#pragma once

#include "glfw/glfw3.h"
#include "glm/glm.hpp"  // IWYU pragma: keep
#include "utils/types.hpp"

extern GLFWwindow* window;

namespace win {

// Create a new window.
void init(cstr title, u32 width, u32 height);
void init(cstr title, glm::vec2 dimensions);

// Change the title of the window.
void title(cstr title);

}  // namespace win
