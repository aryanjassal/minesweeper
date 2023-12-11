#include "glad/glad.h"
#include "utils.hpp"
#include "window.hpp"

#include <stdexcept>

#include "constants.hpp"

GLFWwindow* window = nullptr;
void win::init(const char* title) {
  if (!glfwInit()) {
    throw std::runtime_error("GLFW failed to initialise.");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, false);

  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, nullptr, nullptr);
  if (window == nullptr) {
    throw std::runtime_error("Game window failed to initialise.");
  }

  glfwMakeContextCurrent(window);
  gladLoadGL();
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  // info("OpenGL version is (%s)" + glGetString(GL_VERSION));
}
