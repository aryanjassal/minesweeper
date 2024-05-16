#pragma once

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"  // IWYU pragma: keep
#include "utils/types.hpp"

extern GLFWwindow* window;

namespace win {

// Create a new window.
void init(str title, u32 width, u32 height);
void init(str title, glm::vec2 dimensions);

// Change the title of the window.
void title(str title);

// Destroy the created window and uninitialise GLFW.
void destroy();

}  // namespace win
