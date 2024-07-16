#include "chunk_mesh.hpp"
#include "block.hpp"
#include "block_mesh.hpp"

Player *ChunkMesh::player;

ChunkMesh::~ChunkMesh() {
    vbo.destroy();
    ibo.destroy();
    vao.destroy();
}

ChunkMesh::ChunkMesh(uint64_t *data, glm::vec<2, int> *position) {
    this->data = data;
    this->position = position;

    vao.init();
    vbo.init(GL_ARRAY_BUFFER, STATIC_DRAW);
    ibo.init(GL_ELEMENT_ARRAY_BUFFER, STATIC_DRAW);
}

void ChunkMesh::init(Player *player) {
    ChunkMesh::player = player;
}

void ChunkMesh::render() {
    BlockMesh::shader.bind();
    BlockMesh::shader.uniform_texture_2d(Block::atlas.texture, 0);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    BlockMesh::shader.uniform_mat4("model", model);
    BlockMesh::shader.uniform_mat4("view", player->camera.view);
    BlockMesh::shader.uniform_mat4("projection", player->camera.projection);

    BlockMesh mesh = Block::blocks[BLOCK_GRASS].mesh;

    std::vector<float> vertices;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 3; k++) {
                vertices.push_back(BlockMesh::CUBE_VERTICES[i * FACE_VERTEX_SIZE + j * 3 + k]);
            }
            for (int k = 0; k < 2; k++) {
                vertices.push_back(mesh.faces[i].uv_coordinates[j * 2 + k]);
            }
        }
    }

    // append indices for each face
    std::vector<unsigned int> indices = {
    };

    ibo.buffer(sizeof(BlockMesh::CUBE_INDICES), (void*) BlockMesh::CUBE_INDICES);
    vbo.buffer(vertices.size() * sizeof(float), &vertices[0]);
    vao.attr(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    vao.attr(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));
    vao.bind();

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
