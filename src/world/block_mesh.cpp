#include "block_mesh.hpp"

Shader BlockMesh::shader;

void BlockMesh::init() {
    shader.init("res/shaders/block.vs", "res/shaders/block.fs");
}

void BlockMesh::add_face(Direction direction, glm::vec2 uv_min, glm::vec2 uv_max) {
    faces[direction].uv_min = uv_min;
    faces[direction].uv_max = uv_max;

    float uv_coordinates[] = {
        uv_min.x, 1 - uv_max.y,
        uv_max.x, 1 - uv_max.y,
        uv_min.x, 1 - uv_min.y,
        uv_max.x, 1 - uv_min.y,
    };
    for (int i = 0; i < FACE_UV_COORDINATES_SIZE; i++) {
        faces[direction].uv_coordinates[i] = uv_coordinates[i];
    }
}

void BlockMesh::add_face_vertices(std::vector<float> &vertices, std::vector<float> &indices) {
}
