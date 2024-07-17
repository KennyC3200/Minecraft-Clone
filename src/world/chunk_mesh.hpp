#pragma once

#include "../util/util.hpp"
#include "../gfx/vao.hpp"
#include "../gfx/vbo.hpp"
#include "../player/player.hpp"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16
#define CHUNK_VOLUME (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z)

template<typename T>
struct ChunkMeshBuffer {
    T *data;
    size_t capacity;
    size_t elements;
};

class ChunkMesh {
public:
    ~ChunkMesh();
    ChunkMesh(uint64_t *data, glm::vec<3, int> *position);

    static void init(Player *player);

    void prepare();
    void mesh();
    void render();
private:
    static Player *player;

    ChunkMeshBuffer<float> data_buffer;
    ChunkMeshBuffer<unsigned int> indices_buffer;

    uint64_t *data;
    glm::vec<3, int> *position;

    VAO vao;
    VBO vertex_buffer, uv_buffer;
    VBO ibo;
};
