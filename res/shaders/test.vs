#version 330 core

layout (location = 0) in uint data; // 32 bits 

out vec2 v_uv;

uniform vec3 world_pos;

void main() {
    int pos_x = data         & 31;
    int pos_y = (data >> 6)  & 31;
    int pos_z = (data >> 12) & 31;

    vec3 vertex_pos = (pos_x, pos_y, pos_z);
    gl_Position = world_pos + vertex_pos;

    int u = (data >> 18) & 31;
    int v = (data >> 24) & 31;

    vec2 uv = (u, v);
    v_uv = uv;
}
