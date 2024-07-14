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
    std::cout << "init: " << vao.handle;
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

    glm::vec2 uv_max = Block::blocks[BLOCK_GRASS].mesh.faces[UP].uv_max;
    glm::vec2 uv_min = Block::blocks[BLOCK_GRASS].mesh.faces[UP].uv_min;

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  uv_max.x, 1.0f - uv_min.y,  // top right
         0.5f, -0.5f, 0.0f,  uv_max.x, 1.0f - uv_max.y,  // bottom right
        -0.5f, -0.5f, 0.0f,  uv_min.x, 1.0f - uv_max.y,  // bottom left
        -0.5f,  0.5f, 0.0f,  uv_min.x, 1.0f - uv_min.y,  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    ibo.buffer(sizeof(indices), indices);
    vbo.buffer(sizeof(vertices), vertices);
    vao.attr(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    vao.attr(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));
    vao.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
