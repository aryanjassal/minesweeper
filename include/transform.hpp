#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include "glm/glm.hpp"  // IWYU pragma: keep
#include "utils/types.hpp"

using Transform = struct transform_t {
  glm::vec3 position;
  glm::vec2 scale;
  glm::vec2 origin;
  f32 angle;

  transform_t()
      : position{glm::vec3(0)}, scale{glm::vec2(1)}, angle(0), origin(0) {}
  transform_t(glm::vec3 pos)
      : position{pos}, scale{glm::vec2(1)}, angle(0), origin(0) {}
  transform_t(glm::vec3 pos, glm::vec2 scale)
      : position{pos}, scale{scale}, angle(0), origin(0) {}
  transform_t(glm::vec3 pos, glm::vec2 scale, f32 angle)
      : position{pos}, scale{scale}, angle{angle}, origin(0) {}
};

#endif
