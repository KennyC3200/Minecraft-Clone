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

    // append vertices for each face
    #if 0
    std::vector<float> vertices = {
        // NORTH (-z)
        0, 0, 0, mesh.faces[NORTH].uv_min.x, 1 - mesh.faces[NORTH].uv_max.y,
        1, 0, 0, mesh.faces[NORTH].uv_max.x, 1 - mesh.faces[NORTH].uv_max.y,
        0, 1, 0, mesh.faces[NORTH].uv_min.x, 1 - mesh.faces[NORTH].uv_min.y,
        1, 1, 0, mesh.faces[NORTH].uv_max.x, 1 - mesh.faces[NORTH].uv_min.y,

        // SOUTH (+z)
        0, 0, 1, mesh.faces[SOUTH].uv_min.x, 1 - mesh.faces[SOUTH].uv_max.y,
        1, 0, 1, mesh.faces[SOUTH].uv_max.x, 1 - mesh.faces[SOUTH].uv_max.y,
        0, 1, 1, mesh.faces[SOUTH].uv_min.x, 1 - mesh.faces[SOUTH].uv_min.y,
        1, 1, 1, mesh.faces[SOUTH].uv_max.x, 1 - mesh.faces[SOUTH].uv_min.y,

        // EAST (+x)
        1, 0, 1, mesh.faces[EAST].uv_min.x, 1 - mesh.faces[EAST].uv_max.y,
        1, 0, 0, mesh.faces[EAST].uv_max.x, 1 - mesh.faces[EAST].uv_max.y,
        1, 1, 1, mesh.faces[EAST].uv_min.x, 1 - mesh.faces[EAST].uv_min.y,
        1, 1, 0, mesh.faces[EAST].uv_max.x, 1 - mesh.faces[EAST].uv_min.y,

        // WEST (-x)
        0, 0, 1, mesh.faces[WEST].uv_min.x, 1 - mesh.faces[WEST].uv_max.y,
        0, 0, 0, mesh.faces[WEST].uv_max.x, 1 - mesh.faces[WEST].uv_max.y,
        0, 1, 1, mesh.faces[WEST].uv_min.x, 1 - mesh.faces[WEST].uv_min.y,
        0, 1, 0, mesh.faces[WEST].uv_max.x, 1 - mesh.faces[WEST].uv_min.y,

        // UP (+y)
        0, 1, 1, mesh.faces[UP].uv_min.x, 1 - mesh.faces[UP].uv_max.y,
        1, 1, 1, mesh.faces[UP].uv_max.x, 1 - mesh.faces[UP].uv_max.y,
        0, 1, 0, mesh.faces[UP].uv_min.x, 1 - mesh.faces[UP].uv_min.y,
        1, 1, 0, mesh.faces[UP].uv_max.x, 1 - mesh.faces[UP].uv_min.y,

        // DOWN (-y)
        0, 0, 1, mesh.faces[DOWN].uv_min.x, 1 - mesh.faces[DOWN].uv_max.y,
        1, 0, 1, mesh.faces[DOWN].uv_max.x, 1 - mesh.faces[DOWN].uv_max.y,
        0, 0, 0, mesh.faces[DOWN].uv_min.x, 1 - mesh.faces[DOWN].uv_min.y,
        1, 0, 0, mesh.faces[DOWN].uv_max.x, 1 - mesh.faces[DOWN].uv_min.y,
    };
    #else
    std::vector<float> vertices = {
        // Vertex coordinates
        // NORTH (-z)
        0, 0, 0,
        1, 0, 0,
        0, 1, 0,
        1, 1, 0,

        // SOUTH (+z)
        0, 0, 1,
        1, 0, 1,
        0, 1, 1,
        1, 1, 1,

        // EAST (+x)
        1, 0, 1,
        1, 0, 0,
        1, 1, 1,
        1, 1, 0,

        // WEST (-x)
        0, 0, 1,
        0, 0, 0,
        0, 1, 1,
        0, 1, 0,

        // UP (+y)
        0, 1, 1,
        1, 1, 1,
        0, 1, 0,
        1, 1, 0,

        // DOWN (-y)
        0, 0, 1,
        1, 0, 1,
        0, 0, 0,
        1, 0, 0,

        // UV coordinates
        // NORTH (-z)
        mesh.faces[NORTH].uv_min.x, 1 - mesh.faces[NORTH].uv_max.y,
        mesh.faces[NORTH].uv_max.x, 1 - mesh.faces[NORTH].uv_max.y,
        mesh.faces[NORTH].uv_min.x, 1 - mesh.faces[NORTH].uv_min.y,
        mesh.faces[NORTH].uv_max.x, 1 - mesh.faces[NORTH].uv_min.y,

        // SOUTH (+z)
        mesh.faces[SOUTH].uv_min.x, 1 - mesh.faces[SOUTH].uv_max.y,
        mesh.faces[SOUTH].uv_max.x, 1 - mesh.faces[SOUTH].uv_max.y,
        mesh.faces[SOUTH].uv_min.x, 1 - mesh.faces[SOUTH].uv_min.y,
        mesh.faces[SOUTH].uv_max.x, 1 - mesh.faces[SOUTH].uv_min.y,

        // EAST (+x)
        mesh.faces[EAST].uv_min.x, 1 - mesh.faces[EAST].uv_max.y,
        mesh.faces[EAST].uv_max.x, 1 - mesh.faces[EAST].uv_max.y,
        mesh.faces[EAST].uv_min.x, 1 - mesh.faces[EAST].uv_min.y,
        mesh.faces[EAST].uv_max.x, 1 - mesh.faces[EAST].uv_min.y,

        // WEST (-x)
        mesh.faces[WEST].uv_min.x, 1 - mesh.faces[WEST].uv_max.y,
        mesh.faces[WEST].uv_max.x, 1 - mesh.faces[WEST].uv_max.y,
        mesh.faces[WEST].uv_min.x, 1 - mesh.faces[WEST].uv_min.y,
        mesh.faces[WEST].uv_max.x, 1 - mesh.faces[WEST].uv_min.y,

        // UP (+y)
        mesh.faces[UP].uv_min.x, 1 - mesh.faces[UP].uv_max.y,
        mesh.faces[UP].uv_max.x, 1 - mesh.faces[UP].uv_max.y,
        mesh.faces[UP].uv_min.x, 1 - mesh.faces[UP].uv_min.y,
        mesh.faces[UP].uv_max.x, 1 - mesh.faces[UP].uv_min.y,

        // DOWN (-y)
        mesh.faces[DOWN].uv_min.x, 1 - mesh.faces[DOWN].uv_max.y,
        mesh.faces[DOWN].uv_max.x, 1 - mesh.faces[DOWN].uv_max.y,
        mesh.faces[DOWN].uv_min.x, 1 - mesh.faces[DOWN].uv_min.y,
        mesh.faces[DOWN].uv_max.x, 1 - mesh.faces[DOWN].uv_min.y,
    };
    #endif

    // append indices for each face
    std::vector<unsigned int> indices = {
    };

    ibo.buffer(sizeof(BlockMesh::CUBE_INDICES), (void*) BlockMesh::CUBE_INDICES);
    vbo.buffer(vertices.size() * sizeof(float), &vertices[0]);
    vao.attr(vbo, 0, 3, GL_FLOAT, 0, 0);
    vao.attr(vbo, 1, 2, GL_FLOAT, 0, (4 * 3 * 6) * sizeof(float));
    vao.bind();

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
