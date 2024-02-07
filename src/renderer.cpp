#include "renderer.hpp"

#include <map>
#include <vector>

#include "camera.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"                   // IWYU pragma: keep
#include "glm/gtc/matrix_transform.hpp"  // IWYU pragma: keep
#include "shaders.hpp"
#include "texture.hpp"
#include "utils/logging.hpp"  // IWYU pragma: keep
#include "utils/types.hpp"
#include "vertex.hpp"

#define ROTATION_AXIS glm::vec3(0.0f, 0.0f, 1.0f)

// Keep track of the active renderer
Renderer *active_renderer = nullptr;

// Hashmap to store all the created renderers
std::map<cstr, Renderer> all_renderers = std::map<cstr, Renderer>();

Renderer *Renderers::create(cstr handle, Shader &shader) {
  // Create a new renderer object and get a persistent pointer to it.
  Renderer rend;
  rend.shader = shader;
  rend.handle = handle;
  all_renderers[handle] = rend;
  Renderer *renderer = &all_renderers[handle];

  glGenVertexArrays(1, &renderer->vao);
  glBindVertexArray(renderer->vao);

  glGenBuffers(1, &renderer->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);

  // // For wireframed drawing
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Used `nullptr` here as it doesn't make a difference for the first entry
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(f32) * 5, nullptr);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(f32) * 5,
                        reinterpret_cast<void *>(sizeof(f32) * 3));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  return renderer;
};

Renderer::~Renderer() { glDeleteBuffers(1, &vbo); }

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
}

void Renderer::render(std::vector<vert> verts, Transform transform,
                      Texture texture) {
#ifdef DEBUG
  if (active_camera == nullptr) {
    error("At least one camera must be active!");
  }
#endif

  auto model = glm::mat4(1.0f);

  // Translate
  model = glm::translate(model, transform.position);

  // Rotate around origin
  glm::vec3 origin_offset = glm::vec3(transform.origin * transform.scale, 0.0f);
  model = glm::translate(model, origin_offset);
  model = glm::rotate(model, glm::radians(transform.angle), ROTATION_AXIS);
  model = glm::translate(model, -origin_offset);

  // Scale
  model = glm::scale(model, glm::vec3(transform.scale, 0.0f));

  if (texture.height && texture.width) {
    glActiveTexture(GL_TEXTURE0);
    texture.bind();
  }

  this->shader.set_mat4("model", model);
  this->shader.set_mat4("projection", active_camera->projection);
  this->shader.set_mat4("view", active_camera->view);

  // TODO(aryanj): do the vertices change position? if not, then no need to
  // update them.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vert) * verts.size(), &verts[0],
               GL_DYNAMIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, verts.size());

  // Texture unbind needed?
}
