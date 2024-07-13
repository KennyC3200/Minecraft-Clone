#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex_coord;

out vec2 v_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    v_tex_coord = tex_coord;
}
