#include "chunk_mesh.hpp"
#include "block.hpp"
#include "block_mesh.hpp"

Player *ChunkMesh::player;

ChunkMesh::~ChunkMesh() {
    vertex_buffer.destroy();
    uv_buffer.destroy();
    ibo.destroy();
    vao.destroy();
}

ChunkMesh::ChunkMesh(uint64_t *data, glm::vec<3, int> *position) {
    this->data = data;
    this->position = position;

    vao.init();
    vertex_buffer.init(GL_ARRAY_BUFFER, DYNAMIC_DRAW);
    uv_buffer.init(GL_ARRAY_BUFFER, DYNAMIC_DRAW);
    ibo.init(GL_ELEMENT_ARRAY_BUFFER, DYNAMIC_DRAW);

    data_buffer.data    = new float[(CHUNK_VOLUME / 2) * 6 * 6 * 8];
    indices_buffer.data = new unsigned int[(CHUNK_VOLUME / 2) * 6 * 6];
}

void ChunkMesh::init(Player *player) {
    ChunkMesh::player = player;
}

void ChunkMesh::render() {
    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int z = 0; z < CHUNK_SIZE_Z; z++) {
            for (int y = 0; y < CHUNK_SIZE_Y; y++) {
                Block &block = Block::blocks[data[x * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + y]];
                unsigned int indices[6 * 6] = {0};
                int count = 0;

                if (z + 1 >= CHUNK_SIZE_Z || data[x * CHUNK_SIZE_X + (z + 1) * CHUNK_SIZE_Z + y] == BLOCK_AIR) {
                    for (int i = 0; i < 6; i++) {
                        indices[count * 6 + i] = BlockMesh::CUBE_INDICES[6 * SOUTH + i];
                    }
                    count++;
                }
                if (z - 1 < 0 || data[x * CHUNK_SIZE_X + (z - 1) * CHUNK_SIZE_Z + y] == BLOCK_AIR) {
                    for (int i = 0; i < 6; i++) {
                        indices[count * 6 + i] = BlockMesh::CUBE_INDICES[6 * NORTH + i];
                    }
                    count++;
                }
                if (x + 1 >= CHUNK_SIZE_X || data[(x + 1) * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + y] == BLOCK_AIR) {
                    for (int i = 0; i < 6; i++) {
                        indices[count * 6 + i] = BlockMesh::CUBE_INDICES[6 * EAST + i];
                    }
                    count++;
                }
                if (x - 1 < 0 || data[(x - 1) * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + y] == BLOCK_AIR) {
                    for (int i = 0; i < 6; i++) {
                        indices[count * 6 + i] = BlockMesh::CUBE_INDICES[6 * WEST + i];
                    }
                    count++;
                }
                if (y + 1 >= CHUNK_SIZE_Y || data[x * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + (y + 1)] == BLOCK_AIR) {
                    for (int i = 0; i < 6; i++) {
                        indices[count * 6 + i] = BlockMesh::CUBE_INDICES[6 * UP + i];
                    }
                    count++;
                }
                if (y - 1 < 0 || data[x * CHUNK_SIZE_X + z * CHUNK_SIZE_Z + (y - 1)] == BLOCK_AIR) {
                    for (int i = 0; i < 6; i++) {
                        indices[count * 6 + i] = BlockMesh::CUBE_INDICES[6 * DOWN + i];
                    }
                    count++;
                }

                if (count == 0) {
                    continue;
                }

                glm::mat4 model = glm::translate(
                    glm::mat4(1.0f), 
                    glm::vec3(CHUNK_SIZE_X * position->x + x, 
                              CHUNK_SIZE_Y * position->y + y, 
                              CHUNK_SIZE_Z * position->z + z));
                BlockMesh::shader.uniform_mat4("model", model);

                ibo.buffer(count * 6 * sizeof(unsigned int), indices);
                vertex_buffer.buffer(6 * FACE_VERTEX_SIZE * sizeof(float), (void*) BlockMesh::CUBE_VERTICES);
                uv_buffer.buffer(6 * FACE_UV_COORDINATES_SIZE * sizeof(float), block.mesh.uv_coordinates);

                vao.attr(vertex_buffer, 0, 3, GL_FLOAT, 0, 0);
                vao.attr(uv_buffer, 1, 2, GL_FLOAT, 0, 0);

                vao.bind();
                ibo.bind();

                glDrawElements(GL_TRIANGLES, count * 6, GL_UNSIGNED_INT, 0);
            }
        }
    }
}

void ChunkMesh::mesh() {
}
