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
    Face faces[6];

    faces[UP]    = {atlas.sprite_uv({0, 0}), atlas.sprite_uv({1, 1})};
    faces[DOWN]  = {atlas.sprite_uv({0, 0}), atlas.sprite_uv({1, 1})};
    faces[NORTH] = {atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1})};
    faces[SOUTH] = {atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1})};
    faces[WEST]  = {atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1})};
    faces[EAST]  = {atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1})};
    blocks[BLOCK_GRASS] = Block(BLOCK_GRASS, faces);

    faces[UP]    = {atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1})};
    faces[DOWN]  = {atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1})};
    faces[NORTH] = {atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1})};
    faces[SOUTH] = {atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1})};
    faces[EAST]  = {atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1})};
    faces[WEST]  = {atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1})};
    blocks[BLOCK_DIRT] = Block(BLOCK_DIRT, faces);

    faces[UP]    = {atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1})};
    faces[DOWN]  = {atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1})};
    faces[NORTH] = {atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1})};
    faces[SOUTH] = {atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1})};
    faces[EAST]  = {atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1})};
    faces[WEST]  = {atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1})};
    blocks[BLOCK_STONE] = Block(BLOCK_STONE, faces);
}
