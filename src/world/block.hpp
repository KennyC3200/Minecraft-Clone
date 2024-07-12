#pragma once

#include "block_mesh.hpp"
#include "../gfx/sprite_atlas.hpp"

enum BlockType {
    BLOCK_GRASS = 0,
    BLOCK_STONE,
    BLOCK_LAST
};

class Block {
public:
    Block();
    ~Block();
    Block(BlockType type, BlockMesh mesh);

    static void init();
    static SpriteAtlas atlas;
    static Block blocks[BLOCK_LAST];

    BlockType type;
    BlockMesh mesh;
};
