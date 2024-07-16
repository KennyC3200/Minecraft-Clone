#pragma once

#include "../util/util.hpp"
#include "../gfx/shader.hpp"

#define FACE_VERTEX_SIZE (4 * 3)
#define FACE_UV_COORDINATES_SIZE (4 * 2)

typedef struct {
    glm::vec2 uv_min, uv_max;
    float uv_coordinates[FACE_UV_COORDINATES_SIZE];
} Face;

class BlockMesh {
public:
    void add_face(Direction direction, glm::vec2 uv_min, glm::vec2 uv_max);
    void add_face_vertices(std::vector<float> &vertices, std::vector<float> &indices);

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
    static constexpr unsigned int CUBE_INDICES[] = {
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
