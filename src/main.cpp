// clang-format off
#include "glad/glad.h"
#include <GLFW/glfw3.h>
// clang-format on

#include <chrono>
#include <cmath>
#include <string>

#include "camera.hpp"
#include "keyboard.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "utils/sleep.hpp"
#include "utils/time.hpp"
#include "utils/timer.hpp"
#include "vertex.hpp"
#include "window.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const i32 MAX_FPS = 480;

// TODO use R"()" to make shaders to include them at compile time
// TODO implement batch rendering, making one buffer instead of new draw call
// for each object
// TODO fix random framerate drops

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
auto fps = Timers::create("fps", 100.0f);

void render() {
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto &obj : Objects::all()) {
    obj->render();
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
  kb::update();
}

int main() {
  win::init("Minesweeper", SCREEN_WIDTH, SCREEN_HEIGHT);
  kb::init();

  // TODO get a shader wrapper class like how everything else is
  auto shader = Shader("passthrough");
  shader.compile();

  Renderer *renderer = Renderers::create("default", shader);
  renderer->activate();

  // Create cameras, textures, and objects.
  Camera *cam = Cameras::create_ortho(
      "main", SCREEN_WIDTH, SCREEN_HEIGHT, -100.0f, 100.0f, CAM_ORIGIN_TOP_LEFT
  );
  cam->activate();

  auto mine = Textures::create("one", "assets/cellmine.png");
  auto sq = Objects::create("square", SQUARE_VERTICES, *mine);
  sq->transform = Transform(glm::vec3(0.0f), glm::vec2(100.0f));

  // Define the `delta_start`, `delta_end`, and `update_end` timestamps. The
  // delta time is the actual time between frames, and the update time is used
  // to calculate the sleep time for each frame to not exceed a set framerate.
  std::chrono::high_resolution_clock::time_point d_start, d_end, u_end;

  // This is the main event loop. This loop runs the `render()` and `update()`
  // method in that order.
  // TODO: add some sort of a ticked update too, like `FixedUpdate()` in Unity
  while (!glfwWindowShouldClose(window) && !keys[GLFW_KEY_ESCAPE]) {
    // Calculate the delta time. Note that `.count()` returns the value to the
    // nearest integer, so the division is required to get more accuracy. This
    // converts it from nanoseconds to milliseconds, with a ratio of 1000000:1
    Time::delta =
        std::chrono::duration_cast<std::chrono::nanoseconds>(d_end - d_start)
            .count() /
        1000000.0f;

    d_start = std::chrono::high_resolution_clock::now();
    render();
    update();

    // Use smart sleep to update exactly n times a second, where n is the
    // desired fps of the game.
    u_end = std::chrono::high_resolution_clock::now();
    f64 sleep_time = (1.0f / MAX_FPS) -
                     (std::chrono::duration<f64>(u_end - d_start).count());

    if (sleep_time > 0.0f) smart_sleep(sleep_time, 0.0005f);

    d_end = std::chrono::high_resolution_clock::now();

    if (*Timers::get("fps")) {
      f64 frame_time = Time::delta / 1000.0f;
      u32 fps = std::ceil(1.0f / frame_time);
      win::title("fps: " + std::to_string(fps));
      Timers::reset("fps");
    }
  }

  return 0;
}
