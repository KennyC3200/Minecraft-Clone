#pragma once

#include <vector>

#include "chunk.hpp"

class World {
public:
    World();
    ~World();

    void init();
    void destroy();

    std::vector<Chunk*> chunks;
};
