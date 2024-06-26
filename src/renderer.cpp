#include "renderer.hpp"

#include <algorithm>
#include <vector>

#include "camera.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"                   // IWYU pragma: keep
#include "glm/gtc/matrix_transform.hpp"  // IWYU pragma: keep
#include "shaders.hpp"
#include "texture.hpp"
#include "utils/logging.hpp"
#include "utils/types.hpp"
#include "vertex.hpp"

#define ROTATION_AXIS glm::vec3(0.0f, 0.0f, 1.0f)

// Keep track of the active renderer
Renderer *active_renderer = nullptr;

std::vector<Renderer> all_renderers = std::vector<Renderer>();

Renderer *renderer_manager::create(str handle, Shader &shader, u8 mode) {
  // Create a new renderer object and get a persistent pointer to it.
  Renderer renderer;

  // Set variables on the renderer object, as otherwise, the renderer can
  // falsely delete the actual renderer entry when its destroyed.
  renderer.shader = shader;
  renderer.handle = handle;

  glGenVertexArrays(1, &renderer.vao);
  glBindVertexArray(renderer.vao);

  glGenBuffers(1, &renderer.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);

  // For wireframed drawing
  if (mode == RENDER_WIREFRAME) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  // Used `nullptr` here as it doesn't make a difference for the first entry
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(f32) * 5, nullptr);
  glVertexAttribPointer(
      1, 2, GL_FLOAT, false, sizeof(f32) * 5,
      reinterpret_cast<void *>(sizeof(f32) * 3)
  );
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  all_renderers.push_back(renderer);
  debug("Created new renderer: " + handle);
  return &all_renderers.back();
};

Renderer *renderer_manager::get(id::id_t id) {
  for (auto &rend : all_renderers) {
    if (rend.id == id) return &rend;
  }
  return nullptr;
}

Renderer *renderer_manager::get(str handle) {
  for (auto &rend : all_renderers) {
    if (rend.handle == handle) return &rend;
  }
  return nullptr;
}

bool renderer_manager::destroy(id::id_t id) {
  // Create an iterator which would only contain renderers whose ID is
  // similar to the argument.
  auto it = std::find_if(
      all_renderers.begin(), all_renderers.end(),
      [&](const Renderer &rend) { return rend.id == id; }
  );

  // If the object exists in the array, then erase it. Otherwise, return
  // `false`, signifying something went wrong.
  if (it != all_renderers.end()) {
    all_renderers.erase(it);
    return true;
  }
  return false;
}

void renderer_manager::clear() {
  for (auto &rend : all_renderers) {
    // Delete the buffer and then delete the reference from the hashmap to
    // ensure no dangling references and a clean removal of the renderer. Note
    // that Renderers::remove() is not used as it also removes the entry from
    // the map, which will result in the iterator becoming invalid.

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &rend.vbo);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &rend.vao);
    debug("Deallocated renderer: " + rend.handle);
  }

  all_renderers.clear();
  debug("Cleared all renderers");
}

void Renderer::activate() {
  active_renderer = this;

  // Activate the shader
  this->shader.activate();

  // Activate the renderer if there are more than one renderers. Otherwise this
  // part is redundant (?).
  if (all_renderers.size() == 1) return;
  glBindVertexArray(this->vao);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  debug("Activated renderer: " + this->handle);
}

void Renderer::render(
    std::vector<vert> verts, Transform transform, Texture texture
) {
  // Make sure to have an active camera, otherwise warn the user.
  if (active_camera->handle.empty()) {
    error("At least one camera must be active to perform rendering");
  }

  // Create an empty 4x4 model matrix
  auto model = glm::mat4(1.0f);

  // Translate to the given position
  model = glm::translate(model, transform.position);

  // Rotate around origin to the given angle
  glm::vec3 origin_offset = glm::vec3(transform.origin * transform.scale, 0.0f);
  model = glm::translate(model, origin_offset);
  model = glm::rotate(model, glm::radians(transform.angle), ROTATION_AXIS);
  model = glm::translate(model, -origin_offset);

  // Scale to the given scale factor
  model = glm::scale(model, glm::vec3(transform.scale, 0.0f));

  // Texture must be valid before trying to use it.
  if (texture.height && texture.width) {
    glActiveTexture(GL_TEXTURE0);
    texture.bind();
  }

  this->shader.set_mat4("model", model);
  this->shader.set_mat4("projection", active_camera->projection);
  this->shader.set_mat4("view", active_camera->view);

  // TODO: do the vertices change position? if not, then no need to update them.
  glBufferData(
      GL_ARRAY_BUFFER, sizeof(vert) * verts.size(), &verts[0], GL_DYNAMIC_DRAW
  );
  glDrawArrays(GL_TRIANGLE_STRIP, 0, verts.size());

  // Texture unbind needed?
}
