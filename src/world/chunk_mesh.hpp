#pragma once

#include "../gfx/vao.hpp"
#include "../gfx/vbo.hpp"

class ChunkMesh {
public:
    ChunkMesh();
    ~ChunkMesh();

    void init();
    void destroy();

    VAO vao;
    VBO vbo, ibo;
};
