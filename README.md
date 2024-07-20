# Minecraft

# TODO
- Fix camera snapping

# Future implementations?

## Optimize memory usage (assuming a memory bandwidth bottleneck)
Each vertex is a 32 bit number.
    - 12 bits for position
    - 16 bits for uv_coordinates (0...255 for u and v)
This requires a `uniform vec3 world_pos` variable which is added onwith the vertex position to calculate the final position in the scene.
```glsl
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
```
## Composition over inheritance
ECS? Seems like everyone is using it lol. I can see in some parts why it would be good, but is it really good for performance?
