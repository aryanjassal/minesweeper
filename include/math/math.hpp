#ifndef __MATH_HPP__
#define __MATH_HPP__

#define PI 3.14159265359

#include "typedefs.hpp"

template <typename T>
f32 rad(T angle) {
  return angle * (PI / 180.0f);
}

template <typename T>
f32 deg(T angle) {
  return angle * (180.0f / PI);
}

#endif
