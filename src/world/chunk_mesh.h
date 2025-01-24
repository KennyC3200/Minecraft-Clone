#pragma once

#include <vector>
#include <cstdint>

#include "block.h"
#include "../gfx/vao.h"
#include "../gfx/vbo.h"
#include "../gfx/shader.h"

// Forward declarations
class Chunk;

class ChunkMesh {
public:
    ChunkMesh();
    ~ChunkMesh();

    static void Init();

    void Mesh(Block blocks[], Chunk* adjacent_chunks[6]);
    void Render(glm::ivec3& position);

    static Shader shader;

private:
    VAO vao;
    VBO vbo;
    VBO ibo;

    std::vector<uint32_t> vertices;
    std::vector<uint32_t> indices;
};
