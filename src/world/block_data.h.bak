#pragma once

#include "../gfx/sprite_atlas.h"
#include "block_mesh.h"

enum BlockID {
    BLOCK_NONE = -1,
    BLOCK_AIR = 0,
    BLOCK_GRASS,
    BLOCK_DIRT,
    BLOCK_STONE,
    BLOCK_SAND,
    BLOCK_LOG,
    BLOCK_PLANK,
    BLOCK_LAST,
};

class BlockData {
public:
    BlockData();
    ~BlockData();
    BlockData(enum BlockID id, BlockMesh mesh);

    static SpriteAtlas atlas;
    static BlockData blocks[BLOCK_LAST];

    BlockID id;
    BlockMesh mesh;
private:
    friend class World;

    static void init();
};
