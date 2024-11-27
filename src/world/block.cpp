#include "block.hpp"

Block::Block(BlockID id) {
}

uint Block::get_id() {
    return (data & 0xffff);
}

void Block::set_id(uint id) {
    data = (data & 0xffffffffffff0000) + (uint64_t) id;
}
