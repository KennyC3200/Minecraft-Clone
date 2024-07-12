#include "chunk.hpp"

Chunk::Chunk(glm::vec<2, int> position):
position(position)
{
    data = new uint64_t[CHUNK_VOLUME];
    std::fill(data, data + CHUNK_VOLUME, BLOCK_GRASS);

    mesh.init();
    std::cout << "chunk created\n";
}

Chunk::~Chunk() {
    mesh.destroy();
    delete[] data;

    std::cout << "chunk deleted\n";
}

void Chunk::render() {
    // render one face
    BlockMesh::shader.bind();
    BlockMesh::shader.uniform_texture_2d(Block::atlas.texture, 0);

    glm::vec2 uv_max = Block::blocks[BLOCK_DIRT].mesh.uv_max;
    glm::vec2 uv_min = Block::blocks[BLOCK_DIRT].mesh.uv_min;

    float vertices[] = {
         0.5f,  0.5f, 0.0f,  uv_max.x, 1.0f - uv_min.y,  // top right
         0.5f, -0.5f, 0.0f,  uv_max.x, 1.0f - uv_max.y,  // bottom right
        -0.5f, -0.5f, 0.0f,  uv_min.x, 1.0f - uv_max.y,  // bottom left
        -0.5f,  0.5f, 0.0f,  uv_min.x, 1.0f - uv_min.y,  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    mesh.vbo.buffer(sizeof(vertices), vertices);
    mesh.ibo.buffer(sizeof(indices), indices);
    mesh.vao.attr(mesh.vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    mesh.vao.attr(mesh.vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));
    mesh.vao.bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
