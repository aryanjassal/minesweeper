#version 330 core

out vec4 f_col;
in vec2 uv;

uniform sampler2D sprite;

void main() {
  f_col = texture(sprite, uv);
}
