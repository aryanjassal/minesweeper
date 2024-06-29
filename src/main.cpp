// clang-format off
#include "glad/glad.h"
#include <GLFW/glfw3.h>
// clang-format on

#include <cmath>
#include <string>

#include "camera.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "utils/logging.hpp"
#include "utils/sleep.hpp"
#include "utils/timing.hpp"
#include "vertex.hpp"
#include "window.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const i32 MAX_FPS = 480;

// TODO: use R"()" to make shaders to include them at compile time
// TODO: implement batch rendering, making one buffer instead of new draw call
// for each object
// TODO: use instanced rendering now that we are rendering more objects
// TODO: hide the instantiation from the programmer
// TODO: add a game file and override functions like in unity

// Note that all values should be clamped between 0 and 1, then scaled
// using the transform.scale attribute for maximum control and
// intuitivity.
// clang-format off
const std::vector<vert> SQUARE_VERTICES = {
  vert(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
  vert(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)),
  vert(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
  vert(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f))
};
// clang-format on

void init() {
  // Create timers
  Timers::create("fps", 100.0f);

  // Create a square object with the `cellmine` texture.
  auto texture_mine = Textures::create("one", "assets/cellmine.png");

  u32 size = std::min(SCREEN_HEIGHT, SCREEN_WIDTH) / 10;
  for (u8 i = 0; i < 10; i++) {
    for (u8 j = 0; j < 10; j++) {
      om::create(
          "square" + std::to_string(i) + std::to_string(j), SQUARE_VERTICES,
          texture_mine,
          Transform(glm::vec3(size * i, size * j, 0.0f), glm::vec2(size))
      );
    }
  }
}

void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto &obj : om::all()) {
    obj->render();
  }

  glfwSwapInterval(0);
  glfwSwapBuffers(window);

  // Here as a debug statement in case something goes wrong with OpenGL
  check_gl_errors();
}

void update() {
  // Tick all the timers.
  Timers::tick(timing::delta);

  // Poll new input events before processing them.
  glfwPollEvents();

  // Input processing here

  // Get new keyboard events
  kb::update();
  mouse::update();
}

int main() {
  logging::set_loglevel(LOGLEVEL_DEBUG);

  win::init("Minesweeper", SCREEN_WIDTH, SCREEN_HEIGHT);
  kb::init();
  mouse::init();

  auto &shader = Shaders::create("passthrough");
  shader.compile();

  auto &renderer = Renderers::create("default", shader);
  renderer.activate();

  // Create cameras, textures, and objects.
  auto &cam = Cameras::create_ortho(
      "main", SCREEN_WIDTH, SCREEN_HEIGHT, -100.0f, 100.0f, CAM_ORIGIN_TOP_LEFT
  );
  cam.activate();

  init();

  // This is the main event loop. This loop runs the `render()` and `update()`
  // method in that order. Also defines the `delta_start`, `delta_end`, and
  // `update_end` timestamps to calculate frame times later.
  timing::time_point d_start, d_end, u_end;
  while (!glfwWindowShouldClose(window) && !keys[GLFW_KEY_ESCAPE]) {
    // Calculate the delta time. Note that `.count()` returns the value to the
    // nearest integer, so the division is required to get more accuracy. This
    // converts it from microseconds to milliseconds, with a ratio of 1000:1
    timing::delta =
        timing::duration_cast<timing::microseconds>(d_end - d_start).count() /
        1000.0f;

    d_start = timing::now();
    render();
    update();

    // Use smart sleep to ensure a consistent fps.
    u_end = timing::now();
    f64 sleep_time =
        (1.0f / MAX_FPS) - timing::duration<f64>(u_end - d_start).count();
    smart_sleep(sleep_time);

    d_end = timing::now();

    if (Timers::test("fps")) {
      Timers::reset("fps");
      win::title(
          "Minesweeper - fps: " +
          std::to_string(timing::calculate_fps(timing::delta))
      );
    }
  }

  debug("Closing application...");
  Renderers::clear();
  om::clear();
  win::destroy();
  return 0;
}
