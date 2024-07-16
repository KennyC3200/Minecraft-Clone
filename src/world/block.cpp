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

    BlockMesh mesh;
    mesh.add_face(NORTH, atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(SOUTH, atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(EAST,  atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(WEST,  atlas.sprite_uv({1, 0}), atlas.sprite_uv({2, 1}));
    mesh.add_face(UP,    atlas.sprite_uv({0, 0}), atlas.sprite_uv({1, 1}));
    mesh.add_face(DOWN,  atlas.sprite_uv({2, 0}), atlas.sprite_uv({3, 1}));
    blocks[BLOCK_GRASS] = Block(BLOCK_GRASS, mesh);

    std::cout << "GRASS\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            std::cout << blocks[BLOCK_GRASS].mesh.faces[DOWN].uv_coordinates[i * 2 + j];
        }
        std::cout << '\n';
    }

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
}
