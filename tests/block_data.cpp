#include "../src/world/block.hpp"

int main() {
    BlockData block = 0xff1232131f213213;
    BLOCK_DATA_ID_SET(block, BLOCK_PLANK);
    BLOCK_DATA_LIGHT_SET(block, 15);
    std::cout << BLOCK_DATA_ID_GET(block) << std::endl;
    std::cout << BLOCK_DATA_LIGHT_GET(block) << std::endl;
}
