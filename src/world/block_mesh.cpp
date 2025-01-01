#include "block_mesh.h"

SpriteAtlas BlockMesh::atlas;
BlockMesh BlockMesh::meshes[BLOCK_LAST];

void BlockMesh::Init() {
    atlas.Init("res/images/blocks.png", "blocks", glm::vec2(16, 16));

    BlockMesh mesh;
    mesh.AddFace(NORTH, atlas.SpriteUV({1, 0}), atlas.SpriteUV({2, 1}));
    mesh.AddFace(SOUTH, atlas.SpriteUV({1, 0}), atlas.SpriteUV({2, 1}));
    mesh.AddFace(EAST,  atlas.SpriteUV({1, 0}), atlas.SpriteUV({2, 1}));
    mesh.AddFace(WEST,  atlas.SpriteUV({1, 0}), atlas.SpriteUV({2, 1}));
    mesh.AddFace(UP,    atlas.SpriteUV({0, 0}), atlas.SpriteUV({1, 1}));
    mesh.AddFace(DOWN,  atlas.SpriteUV({2, 0}), atlas.SpriteUV({3, 1}));
    meshes[BLOCK_GRASS] = mesh;

    mesh.AddFace(NORTH, atlas.SpriteUV({2, 0}), atlas.SpriteUV({3, 1}));
    mesh.AddFace(SOUTH, atlas.SpriteUV({2, 0}), atlas.SpriteUV({3, 1}));
    mesh.AddFace(EAST,  atlas.SpriteUV({2, 0}), atlas.SpriteUV({3, 1}));
    mesh.AddFace(WEST,  atlas.SpriteUV({2, 0}), atlas.SpriteUV({3, 1}));
    mesh.AddFace(UP,    atlas.SpriteUV({2, 0}), atlas.SpriteUV({3, 1}));
    mesh.AddFace(DOWN,  atlas.SpriteUV({2, 0}), atlas.SpriteUV({3, 1}));
    meshes[BLOCK_DIRT] = mesh;

    mesh.AddFace(NORTH, atlas.SpriteUV({3, 0}), atlas.SpriteUV({4, 1}));
    mesh.AddFace(SOUTH, atlas.SpriteUV({3, 0}), atlas.SpriteUV({4, 1}));
    mesh.AddFace(EAST,  atlas.SpriteUV({3, 0}), atlas.SpriteUV({4, 1}));
    mesh.AddFace(WEST,  atlas.SpriteUV({3, 0}), atlas.SpriteUV({4, 1}));
    mesh.AddFace(UP,    atlas.SpriteUV({3, 0}), atlas.SpriteUV({4, 1}));
    mesh.AddFace(DOWN,  atlas.SpriteUV({3, 0}), atlas.SpriteUV({4, 1}));
    meshes[BLOCK_STONE] = mesh;

    mesh.AddFace(NORTH, atlas.SpriteUV({4, 0}), atlas.SpriteUV({5, 1}));
    mesh.AddFace(SOUTH, atlas.SpriteUV({4, 0}), atlas.SpriteUV({5, 1}));
    mesh.AddFace(EAST,  atlas.SpriteUV({4, 0}), atlas.SpriteUV({5, 1}));
    mesh.AddFace(WEST,  atlas.SpriteUV({4, 0}), atlas.SpriteUV({5, 1}));
    mesh.AddFace(UP,    atlas.SpriteUV({4, 0}), atlas.SpriteUV({5, 1}));
    mesh.AddFace(DOWN,  atlas.SpriteUV({4, 0}), atlas.SpriteUV({5, 1}));
    meshes[BLOCK_SAND] = mesh;

    mesh.AddFace(NORTH, atlas.SpriteUV({6, 0}), atlas.SpriteUV({7, 1}));
    mesh.AddFace(SOUTH, atlas.SpriteUV({6, 0}), atlas.SpriteUV({7, 1}));
    mesh.AddFace(EAST,  atlas.SpriteUV({6, 0}), atlas.SpriteUV({7, 1}));
    mesh.AddFace(WEST,  atlas.SpriteUV({6, 0}), atlas.SpriteUV({7, 1}));
    mesh.AddFace(UP,    atlas.SpriteUV({5, 0}), atlas.SpriteUV({6, 1}));
    mesh.AddFace(DOWN,  atlas.SpriteUV({5, 0}), atlas.SpriteUV({6, 1}));
    meshes[BLOCK_LOG] = mesh;

    mesh.AddFace(NORTH, atlas.SpriteUV({7, 0}), atlas.SpriteUV({8, 1}));
    mesh.AddFace(SOUTH, atlas.SpriteUV({7, 0}), atlas.SpriteUV({8, 1}));
    mesh.AddFace(EAST,  atlas.SpriteUV({7, 0}), atlas.SpriteUV({8, 1}));
    mesh.AddFace(WEST,  atlas.SpriteUV({7, 0}), atlas.SpriteUV({8, 1}));
    mesh.AddFace(UP,    atlas.SpriteUV({7, 0}), atlas.SpriteUV({8, 1}));
    mesh.AddFace(DOWN,  atlas.SpriteUV({7, 0}), atlas.SpriteUV({8, 1}));
    meshes[BLOCK_PLANK] = mesh;
}

void BlockMesh::Destroy() {
    atlas.Destroy();
}

const SpriteAtlas BlockMesh::GetAtlas() {
    return atlas;
}

const BlockMesh BlockMesh::Get(BlockID block_ID) {
    return meshes[block_ID];
}

void BlockMesh::AddFace(enum Direction direction, glm::vec2 uv_min, glm::vec2 uv_max) {
    faces[direction].uv_min = uv_min;
    faces[direction].uv_max = uv_max;

    float uv_coordinates[] = {
        uv_min.x, 1 - uv_max.y,
        uv_max.x, 1 - uv_max.y,
        uv_min.x, 1 - uv_min.y,
        uv_max.x, 1 - uv_min.y,
    };

    for (int i = 0; i < 2 * 4; i++) {
        faces[direction].uv_coordinates[i] = uv_coordinates[i];
    }
}

void BlockMesh::MeshFace(
    enum Direction direction, 
    glm::vec3 position, 
    std::vector<float>& vertices, 
    std::vector<unsigned int>& indices) const
{
    // Add the indices
    for (int i = 0; i < 6; i++) {
        indices.push_back(vertices.size() / 5 + BlockMesh::indices[i]);
    }

    // Add the vertices
    for (int i = 0; i < 4; i++) {
        // Add the position coordinates
        vertices.push_back(BlockMesh::vertices[3 * 4 * direction + i * 3 + 0] + position.x);
        vertices.push_back(BlockMesh::vertices[3 * 4 * direction + i * 3 + 1] + position.y);
        vertices.push_back(BlockMesh::vertices[3 * 4 * direction + i * 3 + 2] + position.z);

        // Add the uv coordinates
        vertices.push_back(faces[direction].uv_coordinates[i * 2 + 0]);
        vertices.push_back(faces[direction].uv_coordinates[i * 2 + 1]);
    }
}

Face BlockMesh::GetFace(enum Direction direction) const {
    return faces[direction];
}
