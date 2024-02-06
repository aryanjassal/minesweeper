#include "renderer.hpp"

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

Renderer *active_renderer = nullptr;

Renderer::Renderer(Shader &shader) {
  this->shader = shader;

  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);

  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  // // For wireframed drawing
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Used `nullptr` here as it doesn't make a difference for the first entry
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(f32) * 5, nullptr);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(f32) * 5,
                        reinterpret_cast<void *>(sizeof(f32) * 3));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
};

Renderer::~Renderer() { glDeleteBuffers(1, &vbo); }

void Renderer::activate() {
  active_renderer = this;
  this->shader.activate();
}

void Renderer::render(std::vector<vert> verts, Texture texture) {
#ifdef DEBUG
  if (active_camera == nullptr) {
    error("At least one camera must be active!");
  }
#endif

  auto model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));

  if (texture.height && texture.width) {
    glActiveTexture(GL_TEXTURE0);
    texture.bind();
  }

  this->shader.set_mat4("model", model);
  this->shader.set_mat4("projection", active_camera->projection);
  this->shader.set_mat4("view", active_camera->view);

  glBindVertexArray(this->vao);
  // TODO(aryanj): do the vertices change position? if not, then no need to
  // update them.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vert) * verts.size(), &verts[0],
               GL_DYNAMIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, verts.size());

  // Texture unbind needed?
}
