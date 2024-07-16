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
        // NORTH (-z)
        0, 0, 0,
        1, 0, 0,
        0, 1, 0,
        1, 1, 0,

        // SOUTH (+z)
        0, 0, 1,
        1, 0, 1,
        0, 1, 1,
        1, 1, 1,

        // EAST (+x)
        1, 0, 1,
        1, 0, 0,
        1, 1, 1,
        1, 1, 0,

        // WEST (-x)
        0, 0, 1,
        0, 0, 0,
        0, 1, 1,
        0, 1, 0,

        // UP (+y)
        0, 1, 1,
        1, 1, 1,
        0, 1, 0,
        1, 1, 0,

        // DOWN (-y)
        0, 0, 1,
        1, 0, 1,
        0, 0, 0,
        1, 0, 0,
    };
    static constexpr float CUBE_INDICES[] = {
         2,  0,  1,  2,  3,  1, // NORTH (-z)
         6,  4,  5,  6,  7,  5, // SOUTH (+z)
        10,  8,  9, 10, 11,  9, // EAST  (+x)
        14, 12, 13, 14, 15, 13, // WEST  (-x)
        18, 16, 17, 18, 19, 17, // UP    (+y)
        22, 20, 21, 22, 23, 21, // DOWN  (-y)
    };

    Face faces[6];
private:
    friend class Block;

    static void init();
};
