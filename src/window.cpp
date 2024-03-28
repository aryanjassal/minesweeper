// clang-format off
#include "glad/glad.h"
#include <GLFW/glfw3.h>
// clang-format on

#include "window.hpp"

#include <stdexcept>

GLFWwindow* window = nullptr;

void win::init(cstr title, u32 width, u32 height) {
  if (!glfwInit()) {
    throw std::runtime_error("GLFW failed to initialise.");
  }

  if (title == nullptr) {
    title = "";
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, false);
  glfwWindowHint(GLFW_SAMPLES, 16);

  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (window == nullptr) {
    throw std::runtime_error("Game window failed to initialise.");
  }

  glfwMakeContextCurrent(window);
  gladLoadGL();
  glViewport(0, 0, width, height);

  // Enable OpenGL features
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_BLEND);

  // Configure enabled OpenGL features
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void win::init(cstr title, glm::vec2 dimensions) {
  win::init(title, dimensions.x, dimensions.y);
}

void win::title(cstr title) { glfwSetWindowTitle(window, title); }
