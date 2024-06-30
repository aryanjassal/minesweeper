#include "camera.hpp"
#include "game.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "shaders.hpp"
#include "texture.hpp"
#include "utils/logging.hpp"
#include "utils/timing.hpp"
#include "window.hpp"

#define WIDTH 800
#define HEIGHT 600

// TODO: include shaders at compile time
// TODO: implement batch and/or instanced rendering

class Minesweeper : public Game {
  using Game::Game;

  void init() override {
    auto shader = smg::create(
        "passthrough", "src/shaders/pass/pass.vs", "src/shaders/pass/pass.fs"
    );
    shader->compile();

    auto renderer = rmg::create("default", *shader);
    renderer->activate();

    // Create cameras, textures, and objects.
    auto cam = cmg::create_ortho(
        "main", WIDTH, HEIGHT, -100.0f, 100.0f, CAM_ORIGIN_TOP_LEFT
    );
    cam->activate();

    // Create timers
    timer_manager::create("fps", 100.0f);

    // Create a square object with the `cellmine` texture.
    auto texture_mine = txmg::create("one", "assets/cellup.png");

    u32 size = std::min(HEIGHT, WIDTH) / 10;
    for (u8 i = 0; i < 10; i++) {
      for (u8 j = 0; j < 10; j++) {
        str name = "square" + std::to_string(i) + std::to_string(j);
        glm::vec3 position = glm::vec3(size * i, size * j, 0.0f);
        omg::create(
            name, SQUARE_VERTICES, *texture_mine,
            Transform(position, glm::vec2(size))
        );
      }
    }
  }

  void render() override {
    for (auto obj : omg::all()) {
      obj->render();
    }
  }

  void update() override {
    if (timer_manager::test("fps")) {
      timer_manager::reset("fps");
      win::title(
          "Minesweeper - fps: " +
          std::to_string(timing::calculate_fps(timing::delta))
      );
    }
  }
};

int main() {
  logging::set_loglevel(LOGLEVEL_DEBUG);

  Minesweeper minesweeper("Minesweeper", WIDTH, HEIGHT);
  minesweeper.max_fps = 480;
  minesweeper.run();

  return 0;
}
