#version 330 core

layout (location = 0) in uint data;

// Block UV coordinates
out vec2 v_uv;

// For the camera
uniform mat4 mvp;

// Chunk position
uniform ivec3 chunk_pos;

// To calculate the UV coordinates
uniform ivec2 sprites_size;

void main() {
    // Unpack the face position
    ivec3 block_position = ivec3(
        data       & 31u,
        data >> 5  & 31u,
        data >> 10 & 31u
    );

    gl_Position = mvp * vec4(chunk_pos + block_position, 1.0f);

    // Unpack the UV coordinates
    vec2 uv = vec2(
        (data >> 15u & 31u) / float(sprites_size.x),
        (data >> 20u & 31u) / float(sprites_size.y)
    );

    v_uv = uv;
}
