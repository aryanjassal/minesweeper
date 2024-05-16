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
    str handle, u32 width, u32 height, f32 near, f32 far, u8 origin
) {
  Camera cam;
  cam.handle = handle;
  cam.width = width;
  cam.height = height;
  cam.near = near;
  cam.far = far;

  switch (origin) {
    case CAM_ORIGIN_BOTTOM_LEFT: {
      cam.projection = glm::ortho(
          0.0f, static_cast<f32>(width), 0.0f, static_cast<f32>(height), near, far
      );
      break;
    }
    case CAM_ORIGIN_TOP_LEFT: {
      cam.projection = glm::ortho(
          0.0f, static_cast<f32>(width), static_cast<f32>(height), 0.0f, near, far
      );
      break;
    }
    case CAM_ORIGIN_TOP_RIGHT: {
      cam.projection = glm::ortho(
          static_cast<f32>(width), 0.0f, static_cast<f32>(height), 0.0f, near, far
      );
      break;
    }
    case CAM_ORIGIN_BOTTOM_RIGHT: {
      cam.projection = glm::ortho(
          static_cast<f32>(width), 0.0f, 0.0f, static_cast<f32>(height), near, far
      );
      break;
    }
    default: {
      error("Invalid camera origin for " + handle);
    }
  }

  // Save the camera in a hashmap
  all_cameras[handle] = cam;
  debug("Created new orthographic camera: " + handle);
  return &all_cameras[handle];
}

// Create an orthographic camera using a vector for storing dimensions.
// NOTE: The union might cause undefined behaviour. More testing is needed.
Camera *Cameras::create_ortho(
    str handle, glm::uvec2 dimensions, f32 near, f32 far, u8 origin
) {
  return Cameras::create_ortho(handle, dimensions.x, dimensions.y, near, far, origin);
}

// Get a camera using its handle
Camera *Cameras::get(str handle) {
  if (all_cameras.find(handle) == all_cameras.end()) {
    error("Camera '" + handle + "' not found.");
  }
  return &all_cameras[handle];
}
