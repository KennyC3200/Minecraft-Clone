#include "block.h"

Block::Block() {
}

Block::Block(BlockID id)
    : data(0)
{
    set_id(id);
}

uint Block::get_id() {
    return (data & 0xffff);
}

void Block::set_id(uint id) {
    data = (data & 0xffffffffffff0000) + (uint64_t) id;
}
