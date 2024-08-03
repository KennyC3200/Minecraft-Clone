#include "../src/world/block.hpp"

int main() {
    BlockData block = 0xff1232131f213213;
    BLOCK_ID_SET(block, BLOCK_PLANK);
    BLOCK_LIGHT_SET(block, 15);
    std::cout << BLOCK_ID_GET(block) << std::endl;
    std::cout << BLOCK_LIGHT_GET(block) << std::endl;
}
