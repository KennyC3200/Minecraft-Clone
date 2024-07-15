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
        // NORTH (-z) face vertices
        0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0,

        // SOUTH (+z) face vertices
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,
    };
    static constexpr float CUBE_INDICES[] = {
        1, 0, 3, 1, 3, 2, // NORTH (-z)
        5, 4, 7, 5, 7, 6, // SOUTH (+z)
        6, 5, 1, 6, 2, 1, // EAST  (+x)
        4, 7, 3, 4, 0, 3, // WEST  (-x)
        6, 7, 3, 6, 2, 3, // UP    (+y)
        5, 4, 0, 5, 1, 0, // DOWN  (-z)
    };

    Face faces[6];
private:
    friend class Block;

    static void init();
};
