#include "chunk.hpp"

Chunk::Chunk(glm::vec<2, int> position):
position(position)
{
    data = new uint64_t[CHUNK_VOLUME];
    memset(data, BLOCK_GRASS, CHUNK_VOLUME * sizeof(uint64_t));

    std::cout << "chunk created\n";
}

Chunk::~Chunk() {
    delete[] data;

    std::cout << "chunk deleted\n";
}
