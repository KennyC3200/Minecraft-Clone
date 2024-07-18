#include "chunk_mesh.hpp"
#include "block.hpp"
#include "block_mesh.hpp"

Shader ChunkMesh::shader;

ChunkMesh::~ChunkMesh() {
    vbo.destroy();
    ibo.destroy();
    vao.destroy();
}

ChunkMesh::ChunkMesh(uint64_t *data, glm::vec<3, int> *position) {
    this->position = position;
    this->data = data;

    vao.init();
    vbo.init(GL_ARRAY_BUFFER, DYNAMIC_DRAW);
    ibo.init(GL_ELEMENT_ARRAY_BUFFER, DYNAMIC_DRAW);
}

void ChunkMesh::init() {
    shader.init("res/shaders/chunk.vs", "res/shaders/chunk.fs");
}

void ChunkMesh::prepare() {
    vertices.clear();
    indices.clear();
}

void ChunkMesh::mesh() {
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            for (int y = 0; y < CHUNK_SIZE_Y; y++) {
                Block &block = Block::blocks[data[x * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + y]];

                if (z + 1 >= CHUNK_SIZE_Z || data[x * CHUNK_SIZE_X + (z + 1) * CHUNK_SIZE_Z + y] == BLOCK_AIR) {
                    block.mesh.mesh_face(SOUTH, {x, y, z}, vertices, indices);
                }
                if (z - 1 < 0 || data[x * CHUNK_SIZE_X + (z - 1) * CHUNK_SIZE_Z + y] == BLOCK_AIR) {
                    block.mesh.mesh_face(NORTH, {x, y, z}, vertices, indices);
                }
                if (x + 1 >= CHUNK_SIZE_X || data[(x + 1) * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + y] == BLOCK_AIR) {
                    block.mesh.mesh_face(EAST, {x, y, z}, vertices, indices);
                }
                if (x - 1 < 0 || data[(x - 1) * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + y] == BLOCK_AIR) {
                    block.mesh.mesh_face(WEST, {x, y, z}, vertices, indices);
                }
                if (y + 1 >= CHUNK_SIZE_Y || data[x * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + (y + 1)] == BLOCK_AIR) {
                    block.mesh.mesh_face(UP, {x, y, z}, vertices, indices);
                }
                if (y - 1 < 0 || data[x * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + (y - 1)] == BLOCK_AIR) {
                    block.mesh.mesh_face(DOWN, {x, y, z}, vertices, indices);
                }
            }
        }
    }
}

void ChunkMesh::render() {
    glm::mat4 model = glm::translate(
        glm::mat4(1.0f), 
        glm::vec3(
            CHUNK_SIZE_X * position->x,
            CHUNK_SIZE_Y * position->y,
            CHUNK_SIZE_Z * position->z));
    shader.uniform_mat4("model", model);

    ibo.buffer(indices.size() * sizeof(unsigned int), &indices[0]);
    vbo.buffer(vertices.size() * sizeof(float), &vertices[0]);

    vao.attr(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    vao.attr(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

    vao.bind();
    ibo.bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
