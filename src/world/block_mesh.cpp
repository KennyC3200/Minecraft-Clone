#include "block_mesh.hpp"

void BlockMesh::add_face(Direction direction, glm::vec2 uv_min, glm::vec2 uv_max) {
    faces[direction].uv_min = uv_min;
    faces[direction].uv_max = uv_max;

    float _uv_coordinates[] = {
        uv_min.x, 1 - uv_max.y,
        uv_max.x, 1 - uv_max.y,
        uv_min.x, 1 - uv_min.y,
        uv_max.x, 1 - uv_min.y,
    };
    for (int i = 0; i < FACE_UV_COORDINATES_SIZE; i++) {
        faces[direction].uv_coordinates[i] = _uv_coordinates[i];
    }
    for (int i = 0; i < FACE_UV_COORDINATES_SIZE; i++) {
        uv_coordinates[direction * FACE_UV_COORDINATES_SIZE + i] = _uv_coordinates[i];
    }
}
