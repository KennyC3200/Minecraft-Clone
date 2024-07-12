#include "block.hpp"

Block Block::blocks[BLOCK_LAST];
SpriteAtlas Block::atlas;

Block::Block() {}

Block::~Block() {}

Block::Block(BlockType type, BlockMesh mesh):
type(type),
mesh(mesh)
{}

void Block::init() {
    BlockMesh::init();
    atlas = SpriteAtlas("res/images/blocks.png", "blocks", glm::vec2(16, 16));

    blocks[BLOCK_GRASS] = Block(
        BLOCK_GRASS,
        BlockMesh(
            glm::vec2(0.0f, 0.0f), 
            glm::vec2(atlas.sprite_unit.x, atlas.sprite_unit.y))
    );
    // --------------------------
    // have BLOCK_GRASS side mesh
    // --------------------------
    blocks[BLOCK_DIRT] = Block(
        BLOCK_DIRT,
        BlockMesh(
            glm::vec2(2 * atlas.sprite_unit.x, 0.0f),
            glm::vec2(3 * atlas.sprite_unit.x, atlas.sprite_unit.y))
    );
    blocks[BLOCK_STONE] = Block(
        BLOCK_STONE,
        BlockMesh(
            glm::vec2(3 * atlas.sprite_unit.x, 0.0f),
            glm::vec2(4 * atlas.sprite_unit.x, atlas.sprite_unit.y))
    );
}
