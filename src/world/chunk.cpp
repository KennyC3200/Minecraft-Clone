#include "chunk.hpp"

Player* Chunk::player;

Chunk::Chunk(glm::vec<2, int> position):
position(position)
{
    data = new uint64_t[CHUNK_VOLUME];
    std::fill(data, data + CHUNK_VOLUME, BLOCK_GRASS);

    mesh.init();
}

Chunk::~Chunk() {
    mesh.destroy();
    delete[] data;
}

void Chunk::init(Player *player) {
    Chunk::player = player;
}

void Chunk::render() {
    // render one face
    BlockMesh::shader.bind();
    BlockMesh::shader.uniform_texture_2d(Block::atlas.texture, 0);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    BlockMesh::shader.uniform_mat4("model", model);
    BlockMesh::shader.uniform_mat4("view", player->camera.view);
    BlockMesh::shader.uniform_mat4("projection", player->camera.projection);

    glm::vec2 uv_max = Block::blocks[BLOCK_GRASS].mesh.faces[FACE_TOP].uv_max;
    glm::vec2 uv_min = Block::blocks[BLOCK_GRASS].mesh.faces[FACE_TOP].uv_min;

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

    mesh.vbo.buffer(sizeof(vertices), vertices);
    mesh.ibo.buffer(sizeof(indices), indices);
    mesh.vao.attr(mesh.vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    mesh.vao.attr(mesh.vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));
    mesh.vao.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
