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
// TODO: fix random framerate drops
// TODO: use instanced rendering now that we are rendering more objects
// TODO: hide the instantiation from the programmer

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

// Create timers
// TODO: see why `auto fps` cannot be omitted from here
auto fps = Timers::create("fps", 100.0f);

void init() {
  // Create a square object with the `cellmine` texture.
  auto &mine = Textures::create("one", "assets/cellmine.png");

  for (u8 i = 0; i < 10; i++) {
    for (u8 j = 0; j < 10; j++) {
      auto &sq = Objects::create(
          "square" + std::to_string(i) + std::to_string(j), SQUARE_VERTICES,
          mine
      );
      sq.transform =
          Transform(glm::vec3(50.0f * i, 50.0f * j, 0.0f), glm::vec2(50.0f));
    }
  }
}

void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto &obj : Objects::all()) {
    obj.render();
  }

  glfwSwapInterval(0);
  glfwSwapBuffers(window);
}

void update() {
  // Tick all the timers.
  Timers::tick(Time::delta);

  // Poll new input events before processing them.
  glfwPollEvents();

  // Input processing here

  // Get new keyboard events
  // TODO: make the syntax consistent. Probably just need to move evth into a
  // namespace instead of a class
  kb::update();
  Mouse.update();
}

int main() {
  win::init("Minesweeper", SCREEN_WIDTH, SCREEN_HEIGHT);
  kb::init();
  Mouse.init();

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
  Time::time_point d_start, d_end, u_end;
  while (!glfwWindowShouldClose(window) && !keys[GLFW_KEY_ESCAPE]) {
    // Calculate the delta time. Note that `.count()` returns the value to the
    // nearest integer, so the division is required to get more accuracy. This
    // converts it from microseconds to milliseconds, with a ratio of 1000:1
    Time::delta =
        Time::duration_cast<Time::microseconds>(d_end - d_start).count() /
        1000.0f;

    d_start = Time::now();
    render();
    update();

    // Use smart sleep to ensure a consistent fps.
    u_end = Time::now();
    f64 sleep_time =
        (1.0f / MAX_FPS) - Time::duration<f64>(u_end - d_start).count();
    // debug("Sleeping for " + std::to_string(sleep_time));
    smart_sleep(sleep_time, 0.0005f);

    d_end = Time::now();

    if (Timers::test("fps")) {
      Timers::reset("fps");
      win::title("Minesweeper - fps: " + std::to_string(Time::calculate_fps()));
    }
  }

  debug("Closing application...");
  Renderers::clear();
  win::destroy();
  return 0;
}
