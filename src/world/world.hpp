#pragma once

#include <vector>

#include "chunk.hpp"

class World {
public:
    void init();
    void destroy();
    void render();

    Chunk **chunks;
    glm::vec<3, size_t> chunks_size;

    size_t chunks_idx(size_t x, size_t y, size_t z);
    size_t chunks_size_magnitude();
};
