#ifndef __VECTORS_HPP__
#define __VECTORS_HPP__

#include <array>
#include <numeric>
#include <stdexcept>
#include <type_traits>

#include "typedefs.hpp"

// clang-format off
#define CHECK_NUM(T) \
  static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, \
  "vector type must be a numeric or floating type")

#define VEC_OPERATOR_ADD(T, S) T& operator+(float x) \
  { CHECK_NUM(T); for (u8 i = 0; i < S; ++i) { data[i] += x; return data[i]; } }

#define VEC_OPERATOR_SUB(T, S) T& operator-(float x) \
  { CHECK_NUM(T); for (u8 i = 0; i < S; ++i) { data[i] -= x; return data[i]; } }

#define VEC_OPERATOR_MUL(T, S) T& operator*(float x) \
  { CHECK_NUM(T); for (u8 i = 0; i < S; ++i) { data[i] *= x; return data[i]; } }

#define VEC_OPERATOR_DIV(T, S) T& operator/(float x) \
  { CHECK_NUM(T); for (u8 i = 0; i < S; ++i) { data[i] /= x; return data[i]; } }
// clang-format on

// Base vector class
template <typename T, usize L>
class vec {
 private:
  // NOTE: Present only so vectors with arbitrary lengths can access its data
  // using the square brackets operator. This should never be exposed to or used
  // by children classes.
  std::array<T, L> data;

 public:
  constexpr usize size() { return L; }

  VEC_OPERATOR_ADD(T, L);
  VEC_OPERATOR_SUB(T, L);
  VEC_OPERATOR_MUL(T, L);
  VEC_OPERATOR_DIV(T, L);

  // Getter operator
  const T& operator[](const usize i) const {
    if (i < 0 || i > L) {
      throw std::out_of_range("index out of range");
    }
    return this->data[i];
  };

  // Setter operator
  T& operator[](const usize i) {
    if (i < 0 || i > L) {
      throw std::out_of_range("index out of range");
    }
    return this->data[i];
  };

  // TODO: Conversion from any vector to any other vector
};

// Extended _vector classes
template <typename T>
class _vec2 : vec<T, 2> {
 public:
  _vec2() : vec<T, 2>() { construct(0.0f, 0.0f); };
  _vec2(T val) : vec<T, 2>() { construct(val, val); };
  _vec2(T x, T y) : vec<T, 2>() { construct(x, y); };

  void construct(T x, T y) {
    this->x = x;
    this->y = y;
  };

  // clang-format off
  union {
    struct { T x, y; };
    struct { T w, h; };
    std::array<T, 2> data;
  };
  // clang-format on

  VEC_OPERATOR_ADD(T, 2);
  VEC_OPERATOR_SUB(T, 2);
  VEC_OPERATOR_MUL(T, 2);
  VEC_OPERATOR_DIV(T, 2);
};

template <typename T>
class _vec3 : vec<T, 3> {
 public:
  _vec3() : vec<T, 3>() { construct(0.0f, 0.0f, 0.0f); };
  _vec3(T val) : vec<T, 3>() { construct(val, val, val); };
  _vec3(T x, T y) : vec<T, 3>() { construct(x, y, 0.0f); };
  _vec3(T x, T y, T z) : vec<T, 3>() { construct(x, y, z); };

  void construct(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
  };

  // clang-format off
  union {
    struct { T x, y, z; };
    struct { T r, g, b; };
    std::array<T, 3> data;
  };
  // clang-format on

  VEC_OPERATOR_ADD(T, 4);
  VEC_OPERATOR_SUB(T, 4);
  VEC_OPERATOR_MUL(T, 4);
  VEC_OPERATOR_DIV(T, 4);
};

template <typename T>
class _vec4 : vec<T, 4> {
 public:
  _vec4() : vec<T, 4>() { construct(0.0f, 0.0f, 0.0f, 0.0f); };
  _vec4(T val) : vec<T, 4>() { construct(val, val, val, val); };
  _vec4(T x, T y) : vec<T, 4>() { construct(x, y, 0.0f, 0.0f); };
  _vec4(T x, T y, T z) : vec<T, 4>() { construct(x, y, z, 0.0f); };
  _vec4(T x, T y, T z, T w) : vec<T, 4>() { construct(x, y, z, w); };

  void construct(T x, T y, T z, T w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  };

  // clang-format off
  union {
    struct { T x, y, z, w; };
    struct { T r, g, b, a; };
    std::array<T, 4> data;
  };
  // clang-format on

  VEC_OPERATOR_ADD(T, 4);
  VEC_OPERATOR_SUB(T, 4);
  VEC_OPERATOR_MUL(T, 4);
  VEC_OPERATOR_DIV(T, 4);
};

// Vector operations
template <typename T, usize L>
f32 dot(vec<T, L> a, vec<T, L> b) {
  T s = 0;
  // clang-format off
  return std::inner_product(a.data().begin(), a.data().end(), b.data().begin(), s);
  // clang-format on
}

// Vector definitions
using vec2 = _vec2<f32>;
using vec3 = _vec3<f32>;
using vec4 = _vec4<f32>;
using ivec2 = _vec2<i32>;
using ivec3 = _vec3<i32>;
using ivec4 = _vec4<i32>;

#endif
