#pragma once

#include "../util/math.hpp"
#include "../gfx/shader.hpp"

class BlockMesh {
public:
    BlockMesh();
    ~BlockMesh();
    BlockMesh(glm::vec2 uv_min, glm::vec2 uv_max);

    static void init();
    static Shader shader;

    glm::vec2 uv_min, uv_max;
};
