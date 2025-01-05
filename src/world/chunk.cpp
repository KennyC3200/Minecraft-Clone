#include "chunk.h"

FastNoiseLite Chunk::noise;

Chunk::Chunk(glm::ivec3 position, int ground_level_y) {
    this->position = position;

    meshed = false;

    for (int x = 0; x < size.x; x++) {
        for (int z = 0; z < size.z; z++) {
            float noise_y_threshold = ground_level_y + noise.GetNoise<float>(position.x + x, position.z + z) * ground_level_y * 0.2f;
            for (int y = 0; y < size.y; y++) {
                if (position.y + y < noise_y_threshold) {
                    blocks[PosToIdx(x, y, z)] = BLOCK_GRASS;
                } else {
                    blocks[PosToIdx(x, y, z)] = BLOCK_AIR;
                }
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        adjacents[i] = nullptr;
    }
}

void Chunk::Init() {
    ChunkMesh::Init();

    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.01f);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise.SetFractalOctaves(10);
}

int Chunk::PosToIdx(int x, int y, int z) {
    return (x * size.y * size.z) + (z * size.y) + (y);
}

int Chunk::PosToIdx(glm::ivec3 pos) {
    return PosToIdx(pos.x, pos.y, pos.z);
}

void Chunk::Render() {
    if (!meshed) {
        mesh.Mesh(blocks, position, adjacents);
        meshed = true;
    }
    mesh.Render();
}

void Chunk::SetAdjacent(enum Direction direction, Chunk* chunk) {
    adjacents[direction] = chunk;
}

void Chunk::SetDirty() {
    meshed = false;
    for (int i = 0; i < 6; i++) {
        if (adjacents[i] != nullptr) {
            adjacents[i]->meshed = false;
        }
    }
}

Block& Chunk::GetBlock(int x, int y, int z) {
    return blocks[PosToIdx(x, y, z)];
}

Block& Chunk::GetBlock(glm::ivec3 pos) {
    return blocks[PosToIdx(pos)];
}
