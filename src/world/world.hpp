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

    // the center of chunks
    glm::vec3 chunks_center;

    size_t chunks_idx(size_t x, size_t y, size_t z);
    size_t chunks_size_magnitude();
};
