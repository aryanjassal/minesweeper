#version 330 core

layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 tex_coords;

out vec2 uv;

void main() {
  gl_Position = vec4(vert, 1.0);
  uv = tex_coords;
}
