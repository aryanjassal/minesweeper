#ifndef __MATRIX_OPERATIONS_H__
#define __MATRIX_OPERATIONS_H__

#include "math/matrix.hpp"
#include "math/vector.hpp"

// NOTE: Using this methodology instead of templated functions results in
// simpler code and better performance.

// Translate a 4x4 matrix by a 3D vector.
mat4 translate(mat4 m, vec3 v) {
  mat4 out = m;
  m[3] = (m[0] * v[0]) + (m[1] * v[1]) + (m[2] * v[2]) + m[3];
  return m;
}

#endif
