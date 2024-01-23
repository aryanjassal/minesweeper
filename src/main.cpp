#include <iostream>
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "keyboard.hpp"
#include "math/matrix_operations.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "typedefs.hpp"
#include "vertex.hpp"
#include "window.hpp"

// change vertices to three dimensions and start using either <vert> or <v3>
// instead of this, which will make the code more efficient. Clang, don't touch
// this code as it is important for it to remain in this format than whatever
// else the formatter uses.
// clang-format off
const std::vector<vert> SQUARE_VERTICES = {
  vert(vec3( 0.5f, -0.5f), vec2(1.0f, 1.0f)),
  vert(vec3(-0.5f, -0.5f), vec2(0.0f, 1.0f)),
  vert(vec3( 0.5f,  0.5f), vec2(1.0f, 0.0f)),
  vert(vec3(-0.5f,  0.5f), vec2(0.0f, 0.0f))
  // vert(vec3( 0.5f, -0.5f)),
  // vert(vec3(-0.5f, -0.5f)),
  // vert(vec3( 0.5f,  0.5f)),
  // vert(vec3(-0.5f,  0.5f))
};
// clang-format on


void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto &obj : Objects::all()) {
    obj->render();
  }

  glfwSwapBuffers(window);
}

void update() {
  glfwPollEvents();

  // Input processing here

  kb::update();
}

int main() {
  mat4 m(1);
  std::cout << m << std::endl;
  translate(m, vec3(2));
  std::cout << std::endl << m << std::endl;
  return 0;

  win::init("Minesweeper");
  kb::init();

  auto shader = Shader("passthrough");
  shader.compile();

  // TODO(aryanj): need handles in renderer
  auto renderer = Renderer(shader);
  renderer.activate();

  // Create objects and textures 
  Texture *up = Textures::create("one", "assets/cellup.png");
  Object *sq = Objects::create("square", SQUARE_VERTICES, *up);

  // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  while (!glfwWindowShouldClose(window) && !keys[GLFW_KEY_ESCAPE]) {
    render();
    update();
  }

  return 0;
}
