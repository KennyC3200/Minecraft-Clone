#include "block.hpp"

BlockData BlockData::blocks[BLOCK_LAST];
SpriteAtlas BlockData::atlas;

BlockData::BlockData() {}

BlockData::~BlockData() {}

BlockData::BlockData(BlockID id, BlockMesh mesh)
    : id(id), mesh(mesh)
{}

void BlockData::init() {
    atlas = SpriteAtlas("res/images/blocks.png", "blocks", glm::vec2(16, 16));

    BlockMesh mesh;
    mesh.add_face(NORTH, atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({0, 0}), atlas.sprite_uv({1, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    blocks[BLOCK_GRASS] = BlockData(BLOCK_GRASS, mesh);

    mesh.add_face(NORTH, atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    blocks[BLOCK_DIRT] = BlockData(BLOCK_DIRT, mesh);

    mesh.add_face(NORTH, atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    blocks[BLOCK_STONE] = BlockData(BLOCK_STONE, mesh);

    mesh.add_face(NORTH, atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    blocks[BLOCK_SAND] = BlockData(BLOCK_SAND, mesh);

    mesh.add_face(NORTH, atlas.sprite_uv({6, 0}), atlas.sprite_uv({7, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({6, 0}), atlas.sprite_uv({7, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({6, 0}), atlas.sprite_uv({7, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({6, 0}), atlas.sprite_uv({7, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({5, 0}), atlas.sprite_uv({6, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({5, 0}), atlas.sprite_uv({6, 1}));
    blocks[BLOCK_LOG] = BlockData(BLOCK_LOG, mesh);

    mesh.add_face(NORTH, atlas.sprite_uv({7, 0}), atlas.sprite_uv({8, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({7, 0}), atlas.sprite_uv({8, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({7, 0}), atlas.sprite_uv({8, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({7, 0}), atlas.sprite_uv({8, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({7, 0}), atlas.sprite_uv({8, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({7, 0}), atlas.sprite_uv({8, 1}));
    blocks[BLOCK_PLANK] = BlockData(BLOCK_PLANK, mesh);
}
