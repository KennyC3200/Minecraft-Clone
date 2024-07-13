#include "block_mesh.hpp"

Shader BlockMesh::shader;

BlockMesh::BlockMesh() {}

BlockMesh::~BlockMesh() {}

BlockMesh::BlockMesh(glm::vec2 uv_min, glm::vec2 uv_max):
uv_min(uv_min),
uv_max(uv_max) 
{}

void BlockMesh::init() {
    shader.init("res/shaders/block.vs", "res/shaders/block.fs");
}

void BlockMesh::render(bool faces[6]) {
    if (faces[0]) {
        render_face(FACE_UP);
    }
    if (faces[1]) {
        render_face(FACE_DOWN);
    }
    if (faces[2]) {
        render_face(FACE_FRONT);
    }
    if (faces[3]) {
        render_face(FACE_BACK);
    }
    if (faces[4]) {
        render_face(FACE_LEFT);
    }
    if (faces[5]) {
        render_face(FACE_RIGHT);
    }
}

void BlockMesh::render_face(BlockMesh::Face face) {
    switch (face) {
        case FACE_UP:
            break;
        case FACE_DOWN:
            break;
        case FACE_FRONT:
            break;
        case FACE_BACK:
            break;
        case FACE_LEFT:
            break;
        case FACE_RIGHT:
            break;
        default:
            break;
    }
}
