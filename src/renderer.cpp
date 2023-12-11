#include "renderer.hpp"

#include <iostream>
#include <vector>

#include "glad/glad.h"
#include "shaders.hpp"

Renderer *active_renderer = nullptr;

Renderer::Renderer(Shader &shader) {
  this->shader = shader;

  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);

  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

  // For wireframed drawing
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Used `nullptr` here as it doesn't make a difference for the first entry
  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);
  glEnableVertexAttribArray(0);
};

Renderer::~Renderer() { glDeleteBuffers(1, &vbo); }

void Renderer::activate() {
  active_renderer = this;
  this->shader.activate();
}

void Renderer::render(std::vector<f32> vertices) {
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size() / 2);
}
