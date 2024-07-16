#include "chunk.hpp"

Player* Chunk::player;

Chunk::Chunk(glm::vec<3, int> position):
position(position)
{
    data = new uint64_t[CHUNK_VOLUME];
    std::fill(data, data + CHUNK_VOLUME, BLOCK_GRASS);

    mesh = new ChunkMesh(data, &this->position);
}

Chunk::~Chunk() {
    delete mesh;
    delete[] data;
}

void Chunk::init(Player *player) {
    Chunk::player = player;
    ChunkMesh::init(player);
}

void Chunk::render() {
    mesh->render();
}
