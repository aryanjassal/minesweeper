// #include "mesh.hpp"
//
// #include <vector>
//
// #include "glad/glad.h"
// #include "typedefs.hpp"
// #include "vertex.hpp"
//
// Mesh::Mesh(std::vector<vert> vertices, std::vector<u32> indices) {
//   this->vertices = vertices;
//   this->indices = indices;
//
//   glGenVertexArrays(1, &this->vao);
//   glGenBuffers(1, &this->vbo);
//   glGenBuffers(1, &this->ebo);
//
//   glBindVertexArray(this->vao);
//   glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
//
//   glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vert), &vertices[0],
//                GL_STATIC_DRAW);
//
//   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
//   glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32),
//                &indices[0], GL_STATIC_DRAW);
//
//   // vertex positions
//   glEnableVertexAttribArray(0);
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert), (void*)0);
//   // vertex normals
//   glEnableVertexAttribArray(1);
//   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vert),
//                         (void*)offsetof(vert, norm));
//   // vertex texture coords
//   glEnableVertexAttribArray(2);
//   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vert),
//                         (void*)offsetof(vert, tex));
//
//   glBindVertexArray(0);
// }
