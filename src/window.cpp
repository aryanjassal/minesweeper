// clang-format off
#include "glad/glad.h"
#include "utils/logging.hpp"
#include <GLFW/glfw3.h>
// clang-format on

#include "window.hpp"

GLFWwindow* window = nullptr;

void win::init(str title, u32 width, u32 height) {
  if (!glfwInit()) {
    fatal("GLFW failed to initialise");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, false);
  glfwWindowHint(GLFW_SAMPLES, 16);

  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    fatal("Game window failed to initialise.");
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
  
  info("Created new window with title: " + title);
}

void win::init(str title, glm::vec2 dimensions) {
  win::init(title, dimensions.x, dimensions.y);
}

void win::title(str title) { 
  glfwSetWindowTitle(window, title.c_str()); 
  info("Setting window title to: " + title);
}

void win::destroy() {
  glfwMakeContextCurrent(nullptr);
  glfwDestroyWindow(window);
  glfwTerminate();
}
