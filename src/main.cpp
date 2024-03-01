#include <chrono>
#include <cmath>

#include "camera.hpp"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "keyboard.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "utils/time.hpp"
#include "utils/timer.hpp"
#include "vertex.hpp"
#include "window.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// TODO(aryanj): change from #include guards to pragma once
// TODO(aryanj): use R"()" to make shaders to include them at compile time

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

// Create timers
auto fps = Timers::create("fps", 500.0f);
auto physics = Timers::create("physics", 16.6f);

void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto &obj : Objects::all()) {
    obj->transform.angle = 100 * glfwGetTime();
    obj->render();
  }

  glfwSwapInterval(0);
  glfwSwapBuffers(window);
}

void update() {
  // Tick all the timers.
  Timers::tick(Time::delta);

  // if (Timers::test("physics")) {
  //   for (auto &obj : Objects::all()) {
  //     obj->transform.angle = 100 * glfwGetTime();
  //   }
  // }

  // Poll new input events before processing them.
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

  std::chrono::high_resolution_clock::time_point d_start, d_end;
  while (!glfwWindowShouldClose(window) && !keys[GLFW_KEY_ESCAPE]) {
    // Calculate the delta time. Note that `.count()` returns the value to the
    // nearest integer, so the division is required to get more accuracy. This
    // converts it from microseconds to milliseconds, with a ratio of 1000:1
    Time::delta =
        std::chrono::duration_cast<std::chrono::microseconds>(d_end - d_start)
            .count() /
        1000.0f;

    d_start = std::chrono::high_resolution_clock::now();
    render();
    update();
    d_end = std::chrono::high_resolution_clock::now();
    // TODO(aryanj): precise fps control code in (new?) rosewaltz journey code

    // Timer must exist or crash happens.
    if (*Timers::get("fps")) {
      i32 fps = std::ceil(1.0f / static_cast<double>(Time::delta / 1000.0f));
      str s;
      win::title((s + "fps: " + std::to_string(fps)).c_str());
      Timers::reset("fps");
    }
  }

  return 0;
}
