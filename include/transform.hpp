#ifndef __TRANSFORM_HPP__
#define __TRANSFORM_HPP__

#include "typedefs.hpp"
#include "vector.hpp"

using Transform = struct transform_t {
  v3 position;
  v2 scale;
  f32 angle;

  transform_t() : position{v3(0)}, scale{v2(1)}, angle(0) {}
  transform_t(v3 pos) : position{pos}, scale{v2(1)}, angle(0) {}
  transform_t(v3 pos, v2 scale) : position{pos}, scale{scale}, angle(0) {}
  transform_t(v3 pos, v2 scale, f32 angle)
      : position{pos}, scale{scale}, angle{angle} {}
};

#endif
