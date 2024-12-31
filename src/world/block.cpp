#include "block.h"
#include <iostream>

Block::Block() {
    SetID(BLOCK_DIRT);
}

Block::Block(enum BlockID id) {
    data = 0;
    SetID(id);
}

void Block::SetID(enum BlockID id) {
    data = (data & 0xffffffffffff0000L) + id;
}

BlockID Block::GetID() {
    return (BlockID) (data & 0xffff);
}
