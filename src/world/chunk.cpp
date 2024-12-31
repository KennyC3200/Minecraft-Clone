#include "chunk.h"

Chunk::Chunk(glm::ivec3 position) {
    Chunk(position, BLOCK_DIRT);
}

Chunk::Chunk(glm::ivec3 position, BlockID block) {
    this->position = position;

    meshed = false;

    std::fill(blocks, blocks + Chunk::volume, block);

    for (int i = 0; i < 6; i++) {
        adjacents[i] = nullptr;
    }
}

int Chunk::PosToIdx(int x, int y, int z) {
    return (x * size.y * size.z) + (z * size.y) + (y);
}

int Chunk::PosToIdx(glm::ivec3 pos) {
    return PosToIdx(pos.x, pos.y, pos.z);
}

void Chunk::Render() {
    if (!meshed) {
        mesh.Mesh(blocks, position, adjacents);
        meshed = true;
    }
    mesh.Render();
}

void Chunk::SetAdjacent(enum Direction direction, Chunk* chunk) {
    adjacents[direction] = chunk;
}

void Chunk::SetDirty() {
    meshed = false;
    for (int i = 0; i < 6; i++) {
        if (adjacents[i] != nullptr) {
            adjacents[i]->meshed = false;
        }
    }
}

Block& Chunk::GetBlock(int x, int y, int z) {
    return blocks[PosToIdx(x, y, z)];
}

Block& Chunk::GetBlock(glm::ivec3 pos) {
    return blocks[PosToIdx(pos)];
}
