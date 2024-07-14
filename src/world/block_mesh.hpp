#pragma once

#include "../util/util.hpp"
#include "../gfx/shader.hpp"

typedef struct {
    glm::vec2 uv_min, uv_max;
} Face;

class BlockMesh {
public:
    BlockMesh();
    ~BlockMesh();
    BlockMesh(Face faces[6]);

    static Shader shader;
    static constexpr float CUBE_VERTICES[] = {
        // NORTH face (-z)
        0, 0, 0,
        1, 0, 0,
        0, 1, 0,
        1, 1, 0,

        // SOUTH face (+z)
        0, 0, 1,
        1, 0, 1,
        0, 1, 1,
        1, 1, 1,
    };
    static constexpr float CUBE_UVS[] = {
    };

    Face faces[6];
private:
    friend class Block;

    static void init();
};
