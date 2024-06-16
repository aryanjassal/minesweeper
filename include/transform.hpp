#pragma once

#include "glm/glm.hpp"  // IWYU pragma: keep
#include "utils/types.hpp"

#define DEF_P glm::vec3(0)
#define DEF_S glm::vec2(10)
#define DEF_A 0
#define DEF_O glm::vec2(0)

using Transform = struct transform_t {
  glm::vec3 position;
  glm::vec2 scale;
  glm::vec2 origin;
  f32 angle;

  transform_t()
      : position{DEF_P}, scale{DEF_S}, angle(DEF_A), origin(DEF_O) {}
  transform_t(glm::vec3 pos)
      : position{pos}, scale{DEF_S}, angle(DEF_A), origin(DEF_O) {}
  transform_t(glm::vec3 pos, glm::vec2 scale)
      : position{pos}, scale{scale}, angle(DEF_A), origin(DEF_O) {}
  transform_t(glm::vec3 pos, glm::vec2 scale, f32 angle)
      : position{pos}, scale{scale}, angle{angle}, origin(DEF_O) {}
  transform_t(glm::vec3 pos, glm::vec2 scale, f32 angle, glm::vec2 origin)
      : position{pos}, scale{scale}, angle{angle}, origin(origin) {}
};
