#ifndef __VECTORS_HPP__
#define __VECTORS_HPP__

#include <array>
#include <numeric>

#include "typedefs.hpp"

// Base vector
template <usize L, typename T>
class vec {
 public:
  constexpr usize size() { return L; }
};

// Extended vector classes
template <typename T>
class vec2 : public vec<2, T> {
 public:
  vec2(T val) : vec<2, T>() { construct(val, val); };
  vec2(T x, T y) : vec<2, T>() { construct(x, y); };

  void construct(T x, T y) {
    this->x = x;
    this->y = y;
  }

  const T* data() { return &this->x; }

  union {
    struct {
      T x, y;
    };
  };
};

template <typename T>
class vec3 : public vec<3, T> {
 public:
  vec3(T val) : vec<3, T>() { construct(val, val, val); };
  vec3(T x, T y, T z) : vec<3, T>() { construct(x, y, z); };

  void construct(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  const T* data() { return &this->x; }

  union {
    struct {
      T x, y, z;
    };
    struct {
      T r, g, b;
    };
  };
};

template <typename T>
class vec4 : public vec<4, T> {
 public:
  vec4(T val) : vec<4, T>() { construct(val, val, val, val); };
  vec4(T x, T y, T z, T w) : vec<4, T>() { construct(x, y, z, w); };

  void construct(T x, T y, T z, T w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  };

  const T* data() { return &this->x; }

  union {
    struct {
      T x, y, z, w;
    };
    struct {
      T r, g, b, a;
    };
  };
};

// Vector operations
template <usize L, typename T>
f32 dot(vec<L, T> a, vec<L, T> b) {
  T s = 0;
  return std::inner_product(a.data().begin(), a.data().end(), b.data().begin(),
                            s);
}

// Vector definitions
using v2 = vec2<f32>;
using v3 = vec3<f32>;
using v4 = vec4<f32>;
using v2i = vec2<i32>;
using v3i = vec3<i32>;
using v4i = vec4<i32>;

#endif
