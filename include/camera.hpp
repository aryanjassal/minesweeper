#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "glm/glm.hpp"  // IWYU pragma: keep
#include "utils/types.hpp"

class Camera {
 public:
  u32 near, far;
  glm::mat4 projection;
  glm::mat4 view = glm::mat4(1.0f);

  // The dimensions of the camera.
  // clang-format off
  union {
    struct { u32 width; u32 height; };
    glm::uvec2 dimensions;
  };
  // clang-format on

  // Activate the camera and use the projection and view matrices provided by
  // the selected camera.
  void activate();
};

namespace Cameras {

// Create a new orthographic camera.
Camera *create_ortho(cstr handle, u32 width, u32 height, f32 near, f32 far);
Camera *create_ortho(cstr handle, glm::uvec2 dimensions, f32 near, f32 far);

// Get a camera using its handle.
Camera *get(cstr handle);

}  // namespace Cameras

// Store the active camera whose projection and view matrices will be used for
// offsetting objects.
extern Camera *active_camera;

#endif
