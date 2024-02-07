#include "camera.hpp"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "keyboard.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include "window.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Note that all values should be clamped between 0 and 1, then scaled using the
// transform.scale attribute for maximum control and intuitivity.
// clang-format off
const std::vector<vert> SQUARE_VERTICES = {
  vert(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
  vert(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
  vert(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
  vert(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f))
};
// clang-format on

void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto &obj : Objects::all()) {
    obj->transform.angle = 100*glfwGetTime();
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
  win::init("Minesweeper", SCREEN_WIDTH, SCREEN_HEIGHT);
  kb::init();

  auto shader = Shader("passthrough");
  shader.compile();

  Renderer *renderer = Renderers::create("default", shader);
  renderer->activate();

  // Create cameras, textures, and objects.
  Camera *cam = Cameras::create_ortho("main", SCREEN_WIDTH, SCREEN_HEIGHT,
                                      -100.0f, 100.0f);
  cam->activate();

  Texture *mine = Textures::create("one", "assets/cellmine.png");
  Object *sq = Objects::create("square", SQUARE_VERTICES, *mine);
  sq->transform.scale = glm::vec2(100.0f);
  sq->transform.origin = glm::vec2(0.5f);

  while (!glfwWindowShouldClose(window) && !keys[GLFW_KEY_ESCAPE]) {
    render();
    update();
  }

  return 0;
}
