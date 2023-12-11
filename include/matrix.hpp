#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <algorithm>
#include <array>

#include "typedefs.hpp"

// Base class
template <usize C, usize R, typename T>
class matrix {
 public:
  std::array<std::array<T, R>, C> _mat = {};

  const T &data() {
    usize dp = 0;
    for (usize i = 0; i < C; ++i) {
      for (usize j = 0; j < R; ++j) {
        _data[dp] = _mat[i][j];
        dp++;
      }
    }
    return _data[0];
    // return &_mat[0][0];
  }

  // This unlocks advanced functionality not required by most people. Use at
  // your own risk.
  matrix<C, R, T>(T diag) {
    for (i8 i = 0; i < std::min(C, R); ++i) {
      _mat[i][i] = diag;
    }
  }

 private:
  std::array<T, R * C> _data;
};

// Matrix definitions
class m4 : public matrix<4, 4, f32> {
 public:
  m4(f32 init) : matrix<4, 4, f32>(init) {}
};

// NOTE glm::value_ptr() returns the reference of the first element of the
// array. something like mat.data() should work just as well here, and would
// also need storage in memory as one long array of floating points.

#endif
