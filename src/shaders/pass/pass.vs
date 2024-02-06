#version 330 core

layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 tex_coords;

out vec2 uv;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
  gl_Position = projection * view * model * vec4(vert, 1.0);
  uv = tex_coords;
}
