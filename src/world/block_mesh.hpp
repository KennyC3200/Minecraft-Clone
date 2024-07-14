#pragma once

#include "../util/util.hpp"
#include "../gfx/shader.hpp"

enum FaceDirection {
    FACE_TOP = 0,
    FACE_BOTTOM,
    FACE_FRONT,
    FACE_BACK,
    FACE_LEFT,
    FACE_RIGHT,
};

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
private:
    friend class Block;

    static void init();
};
