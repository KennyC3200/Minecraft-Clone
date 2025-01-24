#version 330 core

in vec2 v_uv;

out vec4 frag_color;

uniform sampler2D blocks;

void main() {
    frag_color = texture(blocks, v_uv);
}
