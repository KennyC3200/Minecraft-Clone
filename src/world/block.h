#pragma once

#include <stdint.h>

enum BlockID : uint16_t {
    BLOCK_NONE = 0,
    BLOCK_AIR = 1,
    BLOCK_GRASS,
    BLOCK_DIRT,
    BLOCK_STONE,
    BLOCK_SAND,
    BLOCK_LOG,
    BLOCK_PLANK,
    BLOCK_LAST,
};

class Block {
public:
    Block();
    Block(enum BlockID id);

    void SetID(enum BlockID id);
    BlockID GetID();

private:
    uint64_t data;
};
