#include "chunk_mesh.hpp"

ChunkMesh::ChunkMesh() {}

ChunkMesh::~ChunkMesh() {}

void ChunkMesh::init() {
    vao.init();
    vbo.init(GL_ARRAY_BUFFER, STATIC_DRAW);
    ibo.init(GL_ELEMENT_ARRAY_BUFFER, STATIC_DRAW);
}

void ChunkMesh::destroy() {
    vao.destroy();
}
