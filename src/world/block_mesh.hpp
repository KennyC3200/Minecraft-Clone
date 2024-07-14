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

    Face faces[6];
    static constexpr float VERTICES[6] = {
    };
private:
    friend class Block;

    static void init();
};
