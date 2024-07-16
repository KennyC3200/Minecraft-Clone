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

ChunkMesh::ChunkMesh(uint64_t *data, glm::vec<2, int> *position) {
    this->data = data;
    this->position = position;

    vao.init();
    vertex_buffer.init(GL_ARRAY_BUFFER, STATIC_DRAW);
    uv_buffer.init(GL_ARRAY_BUFFER, STATIC_DRAW);
    ibo.init(GL_ELEMENT_ARRAY_BUFFER, STATIC_DRAW);
}

void ChunkMesh::init(Player *player) {
    ChunkMesh::player = player;
}

void ChunkMesh::render() {
    BlockMesh::shader.bind();
    BlockMesh::shader.uniform_texture_2d(Block::atlas.texture, 0);

    for (int x = 0; x < CHUNK_SIZE_X; x++) {
        for (int y = 0; y < CHUNK_SIZE_Y; y++) {
            for (int z = 0; z < CHUNK_SIZE_Z; z++) {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
                BlockMesh::shader.uniform_mat4("model", model);
                BlockMesh::shader.uniform_mat4("view", player->camera.view);
                BlockMesh::shader.uniform_mat4("projection", player->camera.projection);

                BlockMesh mesh = Block::blocks[BLOCK_GRASS].mesh;
                std::vector<unsigned int> indices = {
                };

                ibo.buffer(sizeof(BlockMesh::CUBE_INDICES), (void*) BlockMesh::CUBE_INDICES);
                vertex_buffer.buffer(6 * FACE_VERTEX_SIZE * sizeof(float), (void*) BlockMesh::CUBE_VERTICES);
                uv_buffer.buffer(6 * FACE_UV_COORDINATES_SIZE * sizeof(float), mesh.uv_coordinates);
                vao.attr(vertex_buffer, 0, 3, GL_FLOAT, 0, 0);
                vao.attr(uv_buffer, 1, 2, GL_FLOAT, 0, 0);
                vao.bind();

                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            }
        }
    }
}
