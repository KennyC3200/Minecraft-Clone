#pragma once

#include "../util/util.hpp"
#include "../gfx/vao.hpp"
#include "../gfx/vbo.hpp"
#include "../player/player.hpp"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16
#define CHUNK_VOLUME (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)

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
    VBO vertex_buffer, uv_buffer;
    VBO ibo;
};
