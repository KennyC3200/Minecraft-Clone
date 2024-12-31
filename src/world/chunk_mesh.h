#pragma once

#include <vector>

#include "block.h"
#include "block_mesh.h"
#include "../util/util.h"
#include "../gfx/vao.h"
#include "../gfx/vbo.h"
#include "../gfx/shader.h"

class Chunk;

class ChunkMesh {
public:
    ChunkMesh();
    ~ChunkMesh();

    static void Init();

    void Mesh(Block blocks[], glm::ivec3 position, Chunk* adjacent_chunks[6]);
    void Render();

    static Shader shader;

private:
    VAO vao;
    VBO vbo;
    VBO ibo;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};
