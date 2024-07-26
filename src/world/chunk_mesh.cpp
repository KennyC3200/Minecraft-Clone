#include "chunk_mesh.hpp"
#include "block.hpp"
#include "block_mesh.hpp"

Shader ChunkMesh::shader;

ChunkMesh::~ChunkMesh() {
    vbo.destroy();
    ibo.destroy();
    vao.destroy();
}

ChunkMesh::ChunkMesh(BlockData *data, glm::ivec3 *position):
data(data),
position(position)
{
    for (int i = 0; i < 6; i++) {
        this->neighbors[i] = neighbors[i];
    }

    vao.init();
    vbo.init(GL_ARRAY_BUFFER, DYNAMIC_DRAW);
    ibo.init(GL_ELEMENT_ARRAY_BUFFER, DYNAMIC_DRAW);
}

void ChunkMesh::init() {
    shader.init("res/shaders/chunk.vs", "res/shaders/chunk.fs");
}

void ChunkMesh::neighbors_set(ChunkMesh *neighbors[6]) {
    for (int i = 0; i < 6; i++) {
        this->neighbors[i] = neighbors[i];
    }
}

void ChunkMesh::prepare() {
    vertices.clear();
    indices.clear();
}

void ChunkMesh::mesh() {
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            for (int y = 0; y < CHUNK_SIZE_Y; y++) {
                Block &block = Block::blocks[data[CHUNK_POS_TO_IDX(x, y, z)]];
                if (block.type == BLOCK_AIR) {
                    continue;
                }

                if (z == CHUNK_SIZE_Z - 1) {
                    if (neighbors[SOUTH] != nullptr && neighbors[SOUTH]->data[CHUNK_POS_TO_IDX(x, y, 0)] == BLOCK_AIR) {
                        block.mesh.mesh_face(SOUTH, {x, y, z}, vertices, indices);
                    }
                } else if (data[CHUNK_POS_TO_IDX(x, y, z + 1)] == BLOCK_AIR) {
                    block.mesh.mesh_face(SOUTH, {x, y, z}, vertices, indices);
                }
                if (z == 0) {
                    if (neighbors[NORTH] != nullptr && neighbors[NORTH]->data[CHUNK_POS_TO_IDX(x, y, CHUNK_SIZE_Z - 1)] == BLOCK_AIR) {
                        block.mesh.mesh_face(NORTH, {x, y, z}, vertices, indices);
                    }
                } else if (data[CHUNK_POS_TO_IDX(x, y, z - 1)] == BLOCK_AIR) {
                    block.mesh.mesh_face(NORTH, {x, y, z}, vertices, indices);
                }
                if (x == CHUNK_SIZE_X - 1) {
                    if (neighbors[EAST] != nullptr && neighbors[EAST]->data[CHUNK_POS_TO_IDX(0, y, z)] == BLOCK_AIR) {
                        block.mesh.mesh_face(EAST, {x, y, z}, vertices, indices);
                    }
                } else if (data[CHUNK_POS_TO_IDX(x + 1, y, z)] == BLOCK_AIR) {
                    block.mesh.mesh_face(EAST, {x, y, z}, vertices, indices);
                }
                if (x == 0) {
                    if (neighbors[WEST] != nullptr && neighbors[WEST]->data[CHUNK_POS_TO_IDX(CHUNK_SIZE_X - 1, y, z)] == BLOCK_AIR) {
                        block.mesh.mesh_face(WEST, {x, y, z}, vertices, indices);
                    }
                } else if (data[CHUNK_POS_TO_IDX(x - 1, y, z)] == BLOCK_AIR) {
                    block.mesh.mesh_face(WEST, {x, y, z}, vertices, indices);
                }
                if (y == CHUNK_SIZE_Y - 1) {
                    if (neighbors[UP] == nullptr || neighbors[UP]->data[CHUNK_POS_TO_IDX(x, 0, z)] == BLOCK_AIR) {
                        block.mesh.mesh_face(UP, {x, y, z}, vertices, indices);
                    }
                } else if (data[CHUNK_POS_TO_IDX(x, y + 1, z)] == BLOCK_AIR) {
                    block.mesh.mesh_face(UP, {x, y, z}, vertices, indices);
                }
                if (y == 0) {
                    if (neighbors[DOWN] != nullptr && neighbors[DOWN]->data[CHUNK_POS_TO_IDX(x, CHUNK_SIZE_Y - 1, z)] == BLOCK_AIR) {
                        block.mesh.mesh_face(DOWN, {x, y, z}, vertices, indices);
                    }
                } else if (data[CHUNK_POS_TO_IDX(x, y - 1, z)] == BLOCK_AIR) {
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
