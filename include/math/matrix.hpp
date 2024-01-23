#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <algorithm>
#include <array>
#include <iostream>

#include "math/vector.hpp"
#include "typedefs.hpp"

// Base class for an n-dimensional matrix.
// C is the number of colums, R is the number of rows, and T is the type of
// elements in the matrix.
template <typename T, usize C, usize R>
class matrix {
 public:
  vec<vec<T, R>, C> data = {};

  static matrix<T, C, R> identity() { return matrix<T, C, R>(1); }

  constexpr usize size() { return C * R; }
  constexpr usize width() { return C; }
  constexpr usize height() { return R; }

  // Returns the data in a one-dimensional array.
  const T &fdata() {
    usize dp = 0;
    std::array<T, C * R> out;
    for (usize i = 0; i < C; ++i) {
      for (usize j = 0; j < R; ++j) {
        out[dp] = data[i][j];
        dp++;
      }
    }
    return out[0];
  }

  // Initialises diagonals in the matrix while also serving as the default
  // constructor.
  matrix<T, C, R>(T diag = 0) {
    for (u8 i = 0; i < std::min(C, R); ++i) {
      data[i][i] = diag;
    }
  }

  // Overload the << operator to allow outputting the matrix to output stream.
  // NOTE: Only works with C++ ostreams and not C printf().
  template <usize Co, usize Ro, typename Ty>
  friend std::ostream &operator<<(std::ostream &os,
                                  const matrix<Ty, Co, Ro> &m);

  // Get the row from row number.
  vec<T, R> &operator[](const usize i) { return data[i]; }
};

template <usize C, usize R, typename T>
std::ostream &operator<<(std::ostream &os, const matrix<T, C, R> &m) {
  for (u8 i = 0; i < C; ++i) {
    for (u8 j = 0; j < R; ++j) {
      os << m.data[i][j] << " ";
    }
    os << std::endl;
  }
  return os;
};

// Matrix definitions
class mat4 : public matrix<f32, 4, 4> {
 public:
  mat4(f32 init) : matrix<f32, 4, 4>(init) {}
};
// NOTE glm::value_ptr() returns the reference of the first element of the
// array. something like mat.data() should work just as well here, and would
// also need storage in memory as one long array of floating points.

#endif
