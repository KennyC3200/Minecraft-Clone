#pragma once

#include <vector>

#include "chunk.hpp"

class World {
public:
    void init();
    void destroy();
    void render();

    Chunk **chunks;

    // the number of chunks
    glm::vec<3, size_t> chunks_size;

    size_t chunks_idx(size_t x, size_t y, size_t z);
    size_t chunks_idx(glm::vec<3, size_t> position);
    size_t chunks_size_magnitude();
};
