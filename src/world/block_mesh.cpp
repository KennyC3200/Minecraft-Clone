#include "block_mesh.h"

SpriteAtlas BlockMesh::atlas;
BlockMesh BlockMesh::meshes[BLOCK_LAST];

void BlockMesh::Init() {
    atlas.Init("res/images/blocks.png", "blocks", glm::vec2(16, 16));

    BlockMesh mesh;
    mesh.AddFace(NORTH, {1, 0}, {2, 1});
    mesh.AddFace(SOUTH, {1, 0}, {2, 1});
    mesh.AddFace(EAST,  {1, 0}, {2, 1});
    mesh.AddFace(WEST,  {1, 0}, {2, 1});
    mesh.AddFace(UP,    {0, 0}, {1, 1});
    mesh.AddFace(DOWN,  {2, 0}, {3, 1});
    meshes[BLOCK_GRASS] = mesh;

    mesh.AddFace(NORTH, {2, 0}, {3, 1});
    mesh.AddFace(SOUTH, {2, 0}, {3, 1});
    mesh.AddFace(EAST,  {2, 0}, {3, 1});
    mesh.AddFace(WEST,  {2, 0}, {3, 1});
    mesh.AddFace(UP,    {2, 0}, {3, 1});
    mesh.AddFace(DOWN,  {2, 0}, {3, 1});
    meshes[BLOCK_DIRT] = mesh;

    mesh.AddFace(NORTH, {3, 0}, {4, 1});
    mesh.AddFace(SOUTH, {3, 0}, {4, 1});
    mesh.AddFace(EAST,  {3, 0}, {4, 1});
    mesh.AddFace(WEST,  {3, 0}, {4, 1});
    mesh.AddFace(UP,    {3, 0}, {4, 1});
    mesh.AddFace(DOWN,  {3, 0}, {4, 1});
    meshes[BLOCK_STONE] = mesh;

    mesh.AddFace(NORTH, {4, 0}, {5, 1});
    mesh.AddFace(SOUTH, {4, 0}, {5, 1});
    mesh.AddFace(EAST,  {4, 0}, {5, 1});
    mesh.AddFace(WEST,  {4, 0}, {5, 1});
    mesh.AddFace(UP,    {4, 0}, {5, 1});
    mesh.AddFace(DOWN,  {4, 0}, {5, 1});
    meshes[BLOCK_SAND] = mesh;

    mesh.AddFace(NORTH, {6, 0}, {7, 1});
    mesh.AddFace(SOUTH, {6, 0}, {7, 1});
    mesh.AddFace(EAST,  {6, 0}, {7, 1});
    mesh.AddFace(WEST,  {6, 0}, {7, 1});
    mesh.AddFace(UP,    {5, 0}, {6, 1});
    mesh.AddFace(DOWN,  {5, 0}, {6, 1});
    meshes[BLOCK_LOG] = mesh;

    mesh.AddFace(NORTH, {7, 0}, {8, 1});
    mesh.AddFace(SOUTH, {7, 0}, {8, 1});
    mesh.AddFace(EAST,  {7, 0}, {8, 1});
    mesh.AddFace(WEST,  {7, 0}, {8, 1});
    mesh.AddFace(UP,    {7, 0}, {8, 1});
    mesh.AddFace(DOWN,  {7, 0}, {8, 1});
    meshes[BLOCK_PLANK] = mesh;
}

void BlockMesh::Destroy() {
    atlas.Destroy();
}

SpriteAtlas& BlockMesh::GetAtlas() {
    return atlas;
}

BlockMesh& BlockMesh::Get(BlockID block_ID) {
    return meshes[block_ID];
}

Face BlockMesh::GetFace(enum Direction direction) {
    return faces[direction];
}

void BlockMesh::AddFace(enum Direction direction, glm::ivec2 sprite_min, glm::ivec2 sprite_max) {
    // UV coordinates
    glm::vec2 uv_min = atlas.SpriteUV(sprite_min);
    glm::vec2 uv_max = atlas.SpriteUV(sprite_max);

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

    // Sprite coordinates
    glm::ivec2 sprites_size = atlas.SpritesSize();

    faces[direction].sprite_coordinates[0] = {sprite_min.x, sprites_size.y - sprite_max.y};
    faces[direction].sprite_coordinates[1] = {sprite_max.x, sprites_size.y - sprite_max.y};
    faces[direction].sprite_coordinates[2] = {sprite_min.x, sprites_size.y - sprite_min.y};
    faces[direction].sprite_coordinates[3] = {sprite_max.x, sprites_size.y - sprite_min.y};
}

void BlockMesh::MeshFace(
    enum Direction direction,
    glm::vec3 position,
    std::vector<float>& vertices,
    std::vector<unsigned int>& indices)
{
    // Add the indices
    for (int i = 0; i < 6; i++) {
        indices.emplace_back(vertices.size() / 5 + BlockMesh::indices[i]);
    }

    // Add the vertices
    for (int i = 0; i < 4; i++) {
        // Add the position coordinates
        vertices.emplace_back(BlockMesh::vertices[3 * 4 * direction + i * 3 + 0] + position.x);
        vertices.emplace_back(BlockMesh::vertices[3 * 4 * direction + i * 3 + 1] + position.y);
        vertices.emplace_back(BlockMesh::vertices[3 * 4 * direction + i * 3 + 2] + position.z);

        // Add the uv coordinates
        vertices.emplace_back(faces[direction].uv_coordinates[i * 2 + 0]);
        vertices.emplace_back(faces[direction].uv_coordinates[i * 2 + 1]);
    }
}
