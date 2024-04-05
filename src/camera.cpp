#include "camera.hpp"

#include <map>

#include "glm/gtc/matrix_transform.hpp"  // IWYU pragma: keep
#include "utils/logging.hpp"
#include "utils/types.hpp"

// Keep track of the active camera
Camera *active_camera = nullptr;

// Hashmap to store all the created cameras
std::map<str, Camera> all_cameras = std::map<str, Camera>();

// Activate a camera
void Camera::activate() { active_camera = this; }

// Create an orthographic camera.
Camera *Cameras::create_ortho(
    str handle, u32 width, u32 height, f32 near, f32 far
) {
  // NOTE: include the handle inside the camera class too???
  Camera cam;
  cam.width = width;
  cam.height = height;
  cam.near = near;
  cam.far = far;
  cam.projection = glm::ortho(
      0.0f, static_cast<f32>(width), 0.0f, static_cast<f32>(height), near, far
  );

  all_cameras[handle] = cam;
  return &all_cameras[handle];
}

// Create an orthographic camera using a vector for storing dimensions.
// NOTE: The union might cause undefined behaviour. More testing is needed.
Camera *Cameras::create_ortho(
    str handle, glm::uvec2 dimensions, f32 near, f32 far
) {
  return Cameras::create_ortho(handle, dimensions.x, dimensions.y, near, far);
}

// Get a camera using its handle
Camera *Cameras::get(str handle) {
  if (all_cameras.find(handle) == all_cameras.end()) {
    str s;
    error(s + "Camera '" + handle + "'not found.");
  }
  return &all_cameras[handle];
}
