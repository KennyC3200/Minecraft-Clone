#include "block_mesh.hpp"

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

void BlockMesh::mesh_face(
    Direction direction,
    glm::ivec3 position,
    std::vector<float> &vertices,
    std::vector<unsigned int> &indices)
{
    for (int i = 0; i < 6; i++) {
        indices.push_back(vertices.size() / 5 + BlockMesh::INDICES[i]);
    }
    for (int i = 0; i < 4; i++) {
        vertices.push_back(VERTICES[3 * 4 * direction + i * 3 + 0] + position.x);
        vertices.push_back(VERTICES[3 * 4 * direction + i * 3 + 1] + position.y);
        vertices.push_back(VERTICES[3 * 4 * direction + i * 3 + 2] + position.z);
        vertices.push_back(faces[direction].uv_coordinates[i * 2]);
        vertices.push_back(faces[direction].uv_coordinates[i * 2 + 1]);
    }
}
