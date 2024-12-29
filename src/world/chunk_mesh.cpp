#include "chunk_mesh.h"
#include "block.h"
#include "block_mesh.h"

Shader ChunkMesh::shader;

ChunkMesh::ChunkMesh(Block *blocks, glm::ivec3 *position)
    : blocks(blocks) , position(position)
{
    for (int i = 0; i < 6; i++) {
        this->neighbors[i] = neighbors[i];
    }

    vao.init(); 
    vbo.init(GL_ARRAY_BUFFER, DYNAMIC_DRAW);
    ibo.init(GL_ELEMENT_ARRAY_BUFFER, DYNAMIC_DRAW);
}

ChunkMesh::~ChunkMesh() {
    vbo.destroy();
    ibo.destroy();
    vao.destroy();
}

void ChunkMesh::init() {
    shader.init("res/shaders/chunk.vs", "res/shaders/chunk.fs");
}

int ChunkMesh::chunk_pos_to_idx(glm::ivec3 pos) {
    return (pos.x * CHUNK_SIZE.z * CHUNK_SIZE.y + pos.z * CHUNK_SIZE.y + pos.y);
}

int ChunkMesh::chunk_pos_to_idx(int x, int y, int z) {
    return (x * CHUNK_SIZE.z * CHUNK_SIZE.y + z * CHUNK_SIZE.y + y);
}

void ChunkMesh::neighbors_set(ChunkMesh *neighbors[6]) {
    for (int i = 0; i < 6; i++) {
        this->neighbors[i] = neighbors[i];
    }
}

void ChunkMesh::mesh() {
    vertices.clear();
    indices.clear();

    // Wtf is this devious code?
    for (int x = 0; x < ChunkMesh::CHUNK_SIZE.x; x++) {
        for (int z = 0; z < ChunkMesh::CHUNK_SIZE.z; z++) {
            for (int y = 0; y < ChunkMesh::CHUNK_SIZE.y; y++) {
                BlockData &block = BlockData::blocks[blocks[ChunkMesh::chunk_pos_to_idx(x, y, z)].get_id()];
                if (block.id == BLOCK_AIR) {
                    continue;
                }

                if (z == ChunkMesh::CHUNK_SIZE.z - 1) {
                    if (neighbors[SOUTH] != nullptr && (neighbors[SOUTH]->blocks[ChunkMesh::chunk_pos_to_idx(x, y, 0)]).get_id() == BLOCK_AIR) {
                        block.mesh.mesh_face(SOUTH, {x, y, z}, vertices, indices);
                    }
                } else if (blocks[ChunkMesh::chunk_pos_to_idx(x, y, z + 1)].get_id() == BLOCK_AIR) {
                    block.mesh.mesh_face(SOUTH, {x, y, z}, vertices, indices);
                }
                if (z == 0) {
                    if (neighbors[NORTH] != nullptr && (neighbors[NORTH]->blocks[ChunkMesh::chunk_pos_to_idx(x, y, ChunkMesh::CHUNK_SIZE.z - 1)]).get_id() == BLOCK_AIR) {
                        block.mesh.mesh_face(NORTH, {x, y, z}, vertices, indices);
                    }
                } else if (blocks[ChunkMesh::chunk_pos_to_idx(x, y, z - 1)].get_id() == BLOCK_AIR) {
                    block.mesh.mesh_face(NORTH, {x, y, z}, vertices, indices);
                }
                if (x == ChunkMesh::CHUNK_SIZE.x - 1) {
                    if (neighbors[EAST] != nullptr && (neighbors[EAST]->blocks[ChunkMesh::chunk_pos_to_idx(0, y, z)]).get_id() == BLOCK_AIR) {
                        block.mesh.mesh_face(EAST, {x, y, z}, vertices, indices);
                    }
                } else if (blocks[ChunkMesh::chunk_pos_to_idx(x + 1, y, z)].get_id() == BLOCK_AIR) {
                    block.mesh.mesh_face(EAST, {x, y, z}, vertices, indices);
                }
                if (x == 0) {
                    if (neighbors[WEST] != nullptr && (neighbors[WEST]->blocks[ChunkMesh::chunk_pos_to_idx(ChunkMesh::CHUNK_SIZE.x - 1, y, z)]).get_id() == BLOCK_AIR) {
                        block.mesh.mesh_face(WEST, {x, y, z}, vertices, indices);
                    }
                } else if (blocks[ChunkMesh::chunk_pos_to_idx(x - 1, y, z)].get_id() == BLOCK_AIR) {
                    block.mesh.mesh_face(WEST, {x, y, z}, vertices, indices);
                }
                if (y == ChunkMesh::CHUNK_SIZE.y - 1) {
                    if (neighbors[UP] == nullptr || (neighbors[UP]->blocks[ChunkMesh::chunk_pos_to_idx(x, 0, z)]).get_id() == BLOCK_AIR) {
                        block.mesh.mesh_face(UP, {x, y, z}, vertices, indices);
                    }
                } else if (blocks[ChunkMesh::chunk_pos_to_idx(x, y + 1, z)].get_id() == BLOCK_AIR) {
                    block.mesh.mesh_face(UP, {x, y, z}, vertices, indices);
                }
                if (y == 0) {
                    if (neighbors[DOWN] != nullptr && (neighbors[DOWN]->blocks[ChunkMesh::chunk_pos_to_idx(x, ChunkMesh::CHUNK_SIZE.y - 1, z)]).get_id() == BLOCK_AIR) {
                        block.mesh.mesh_face(DOWN, {x, y, z}, vertices, indices);
                    }
                } else if (blocks[ChunkMesh::chunk_pos_to_idx(x, y - 1, z)].get_id() == BLOCK_AIR) {
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
            ChunkMesh::CHUNK_SIZE.x * position->x,
            ChunkMesh::CHUNK_SIZE.y * position->y,
            ChunkMesh::CHUNK_SIZE.z * position->z));
    shader.uniform_mat4("model", model);

    ibo.buffer(indices.size() * sizeof(unsigned int), &indices[0]);
    vbo.buffer(vertices.size() * sizeof(float), &vertices[0]);

    vao.attr(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0 * sizeof(float));
    vao.attr(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

    vao.bind();
    ibo.bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
