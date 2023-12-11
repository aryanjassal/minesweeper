#include <array>
#include <cstdio>
#include <iostream>

#include "constants.hpp"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "keyboard.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "shaders.hpp"
#include "typedefs.hpp"
#include "vertex.hpp"
#include "window.hpp"

const std::vector<f32> SQUARE_VERTICES = { 
  0.5f, -0.5f,
  -0.5f, -0.5f,
  0.5f, 0.5f,
  -0.5f, 0.5f
};

Object sq = Object("square", SQUARE_VERTICES);

void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  sq.render();

  glfwSwapBuffers(window);
}

void update() {
  glfwPollEvents();

  // Input processing here

  kb::update();
}

int main() {
  win::init("Minesweeper");
  kb::init();

  auto shader = Shader("passthrough");
  shader.compile();

  // TODO(aryanj): need handles in renderer
  auto renderer = Renderer(shader);
  renderer.activate();

  while (!glfwWindowShouldClose(window) && !keys[GLFW_KEY_ESCAPE]) {
    render();
    update();
  }

  return 0;
}
