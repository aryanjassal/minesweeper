#version 330 core

out vec4 f_col;
in vec2 uv;

uniform sampler2D sprite;

void main() {
  // f_col = texture(sprite, uv);
  // f_col = vec4(uv, 1.0, 1.0);
  f_col = vec4(1.0);
}
