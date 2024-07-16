#pragma once

#include "../gfx/sprite_atlas.hpp"
#include "block_mesh.hpp"

enum BlockType {
    BLOCK_GRASS = 0,
    BLOCK_DIRT,
    BLOCK_STONE,
    BLOCK_SAND,
    BLOCK_LAST
};

class Block {
public:
    Block();
    ~Block();
    Block(BlockType type, BlockMesh mesh);

    static SpriteAtlas atlas;
    static Block blocks[BLOCK_LAST];

    BlockType type;
    BlockMesh mesh;
private:
    friend class World;

    static void init();
};
