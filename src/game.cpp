// clang-format off
#include "glad/glad.h"
#include <GLFW/glfw3.h>
// clang-format on

#include "game.hpp"

#include "keyboard.hpp"
#include "mouse.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "utils/logging.hpp"
#include "utils/sleep.hpp"
#include "utils/timing.hpp"
#include "window.hpp"

void Game::pre_init() {
  win::init(title, this->screen_width, this->screen_height);
  kb::init();
  mouse::init();
}

void Game::init() {}

void Game::post_init() {}

void Game::run() {
  this->pre_init();
  this->init();
  this->post_init();

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
    this->pre_render();
    this->render();
    this->post_render();

    this->pre_update();
    this->update();
    this->post_update();
    u_end = timing::now();

    // Use smart sleep to ensure a consistent fps.
    f64 min_frame_time = 1.0f / max_fps;
    f64 sleep_time =
        min_frame_time - timing::duration<f64>(u_end - d_start).count();
    smart_sleep(sleep_time);

    d_end = timing::now();
  }
}

void Game::pre_update() {
  timer_manager::tick(timing::delta);
  glfwPollEvents();
}

void Game::update() {}

void Game::post_update() {
  kb::update();
  mouse::update();
}

void Game::pre_render() { glClear(GL_COLOR_BUFFER_BIT); }

void Game::render() {}

void Game::post_render() {
  glfwSwapInterval(0);
  glfwSwapBuffers(window);

  // Here as a debug statement in case something goes wrong with OpenGL
  check_gl_errors();
}

Game::Game(str title, u32 screen_width, u32 screen_height) {
  this->title = title;
  this->screen_width = screen_width;
  this->screen_height = screen_height;
}

Game::~Game() {
  debug("Closing application...");
  rmg::clear();
  omg::clear();
  win::destroy();
}
