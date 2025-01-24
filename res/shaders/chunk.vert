#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

// Block UV coordinates
out vec2 v_uv;

// For the camera
uniform mat4 view;
uniform mat4 projection;

// Chunk position
uniform ivec3 chunk_pos;

// To calculate the UV coordinates
uniform vec2 sprites_size;

void main() {
    gl_Position = projection * view * vec4(chunk_pos + position, 1.0f);
    v_uv = uv;
}
