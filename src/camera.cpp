#include "camera.hpp"

#include "glm/gtc/matrix_transform.hpp"  // IWYU pragma: keep
#include "utils/id.hpp"
#include "utils/logging.hpp"
#include "utils/types.hpp"

// Keep track of the active camera
Camera *active_camera = nullptr;

// Hashmap to store all the created cameras
std::vector<Camera> all_cameras = std::vector<Camera>();

// Activate a camera
void Camera::activate() {
  active_camera = this;
  debug("Activated camera: " + this->handle);
}

// Create an orthographic camera.
Camera *camera_manager::create_ortho(
    str handle, u32 width, u32 height, f32 near, f32 far, u8 origin
) {
  Camera cam;
  cam.handle = handle;
  cam.width = width;
  cam.height = height;
  cam.near = near;
  cam.far = far;

  switch (origin) {
    case CAM_ORIGIN_BOTTOM_LEFT:
      cam.projection = glm::ortho(
          0.0f, static_cast<f32>(width), 0.0f, static_cast<f32>(height), near,
          far
      );
      break;

    case CAM_ORIGIN_TOP_LEFT:
      cam.projection = glm::ortho(
          0.0f, static_cast<f32>(width), static_cast<f32>(height), 0.0f, near,
          far
      );
      break;

    case CAM_ORIGIN_TOP_RIGHT:
      cam.projection = glm::ortho(
          static_cast<f32>(width), 0.0f, static_cast<f32>(height), 0.0f, near,
          far
      );
      break;

    case CAM_ORIGIN_BOTTOM_RIGHT:
      cam.projection = glm::ortho(
          static_cast<f32>(width), 0.0f, 0.0f, static_cast<f32>(height), near,
          far
      );
      break;

    default:
      error("Invalid camera origin for camera:" + handle);
  }

  all_cameras.push_back(cam);
  debug("Created new orthographic camera: " + handle);
  return &all_cameras.back();
}

Camera *camera_manager::create_ortho(
    str handle, glm::uvec2 dimensions, f32 near, f32 far, u8 origin
) {
  return camera_manager::create_ortho(
      handle, dimensions.x, dimensions.y, near, far, origin
  );
}

Camera *camera_manager::get(id::id_t id) {
  for (auto &cam : all_cameras) {
    if (cam.id == id) return &cam;
  }
  return nullptr;
}

Camera *camera_manager::get(str handle) {
  for (auto &cam : all_cameras) {
    if (cam.handle == handle) return &cam;
  }
  return nullptr;
}
