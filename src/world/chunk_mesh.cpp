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

    glm::vec2 uv_max = Block::blocks[BLOCK_GRASS].mesh.faces[NORTH].uv_max;
    glm::vec2 uv_min = Block::blocks[BLOCK_GRASS].mesh.faces[NORTH].uv_min;

    float vertices[] = {
        // NORTH (-z) face vertices
        0, 0, 0,  uv_min.x, 1 - uv_max.y, // bottom left
        1, 0, 0,  uv_max.x, 1 - uv_max.y, // bottom right
        1, 1, 0,  uv_max.x, 1 - uv_min.y, // top right
        0, 1, 0,  uv_min.x, 1 - uv_min.y, // top left

        // SOUTH (+z) face vertices
        0, 0, 1,  uv_min.x, 1 - uv_max.y, // bottom left
        1, 0, 1,  uv_max.x, 1 - uv_max.y, // bottom right
        1, 1, 1,  uv_max.x, 1 - uv_min.y, // top right
        0, 1, 1,  uv_min.x, 1 - uv_min.y, // top left
    };
    unsigned int indices[] = {
        1, 0, 3, 1, 3, 2, // NORTH (-z)
        5, 4, 7, 5, 7, 6, // SOUTH (+z)
        6, 5, 1, 6, 2, 1, // EAST  (+x)
        4, 7, 3, 4, 0, 3, // WEST  (-x)
        6, 7, 3, 6, 2, 3, // UP    (+y)
        5, 4, 0, 5, 3, 0, // DOWN  (-z)
    };

    ibo.buffer(sizeof(indices), indices);
    vbo.buffer(sizeof(vertices), vertices);
    vao.attr(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    vao.attr(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));
    vao.bind();

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
