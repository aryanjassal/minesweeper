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

// change vertices to three dimensions and start using either <vert> or <v3>
// instead of this, which will make the code more efficient. Clang, don't touch
// this code as it is important for it to remain in this format than whatever
// else the formatter uses.
// clang-format off
const std::vector<vert> SQUARE_VERTICES = {
  vert(glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 1.0f)),
  vert(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 1.0f)),
  vert(glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec2(1.0f, 0.0f)),
  vert(glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec2(0.0f, 0.0f))
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
  win::init("Minesweeper", SCREEN_WIDTH, SCREEN_HEIGHT);
  kb::init();

  auto shader = Shader("passthrough");
  shader.compile();

  // TODO(aryanj): need handles in renderer
  auto renderer = Renderer(shader);
  renderer.activate();

  // Create objects and textures
  Texture *mine = Textures::create("one", "assets/cellmine.png");
  Object *sq = Objects::create("square", SQUARE_VERTICES, *mine);
  Camera *cam = Cameras::create_ortho("main", 8, 6,
                                      -100.0f, 100.0f);
  cam->activate();

  while (!glfwWindowShouldClose(window) && !keys[GLFW_KEY_ESCAPE]) {
    render();
    update();
  }

  return 0;
}
