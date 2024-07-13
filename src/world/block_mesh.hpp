#pragma once

#include "../util/util.hpp"
#include "../gfx/shader.hpp"

class BlockMesh {
public:
    BlockMesh();
    ~BlockMesh();
    BlockMesh(glm::vec2 uv_min, glm::vec2 uv_max);

    static Shader shader;

    glm::vec2 uv_min, uv_max;
private:
    friend class Block;

    static void init();
};
