#pragma once

#include "../util/util.hpp"
#include "../gfx/shader.hpp"

class BlockMesh {
public:
    BlockMesh();
    ~BlockMesh();
    BlockMesh(glm::vec2 uv_min, glm::vec2 uv_max);

    enum Face {
        FACE_UP = 0,
        FACE_DOWN,
        FACE_FRONT,
        FACE_BACK,
        FACE_LEFT,
        FACE_RIGHT
    };

    void render(bool faces[6]);
    void render_face(BlockMesh::Face face);

    static Shader shader;

    glm::vec2 uv_min, uv_max;
private:
    friend class Block;

    static void init();
};
