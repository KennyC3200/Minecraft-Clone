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
    atlas = SpriteAtlas("res/images/blocks.png", "blocks", glm::vec2(16, 16));

    BlockMesh mesh;
    mesh.add_face(NORTH, atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({0, 0}), atlas.sprite_uv({1, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    blocks[BLOCK_GRASS] = Block(BLOCK_GRASS, mesh);

    mesh.add_face(NORTH, atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    blocks[BLOCK_DIRT] = Block(BLOCK_DIRT, mesh);

    mesh.add_face(NORTH, atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({3, 0}), atlas.sprite_uv({4, 1}));
    blocks[BLOCK_STONE] = Block(BLOCK_STONE, mesh);

    mesh.add_face(NORTH, atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({4, 0}), atlas.sprite_uv({5, 1}));
    blocks[BLOCK_SAND] = Block(BLOCK_SAND, mesh);
}
