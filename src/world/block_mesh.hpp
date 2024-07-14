#pragma once

#include "../util/util.hpp"
#include "../gfx/shader.hpp"

// assign each face direction enum value a key to the corresponding model matrix
enum FaceDirection {
    FACE_TOP = 0,
    FACE_BOTTOM,
    FACE_FRONT,
    FACE_BACK,
    FACE_LEFT,
    FACE_RIGHT,
    FACE_FIRST = FACE_TOP,
    FACE_LAST = FACE_RIGHT,
};

typedef struct {
    glm::vec2 uv_min, uv_max;
    glm::mat4 model;
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
