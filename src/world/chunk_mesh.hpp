#pragma once

#include "../util/util.hpp"
#include "../gfx/vao.hpp"
#include "../gfx/vbo.hpp"
#include "../player/player.hpp"

class ChunkMesh {
public:
    ~ChunkMesh();
    ChunkMesh(uint64_t *data, glm::vec<2, int> *position);

    static void init(Player *player);
    void render();
private:
    static Player *player;

    uint64_t *data;
    glm::vec<2, int> *position;

    VAO vao;
    VBO vbo, ibo;
};
