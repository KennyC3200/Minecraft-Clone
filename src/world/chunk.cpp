#include "chunk.h"

FastNoiseLite Chunk::noise;

Chunk::Chunk() {}

Chunk::Chunk(glm::ivec3 position, int ground_level) {
    this->position = position;

    meshed = false;

    // Generate the chunk
    Generate(position, ground_level);

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

void Chunk::Generate(glm::ivec3 position, int ground_level) {
    this->position = position;

    for (int x = 0; x < size.x; x++) {
        for (int z = 0; z < size.z; z++) {
            float noise_val = 
                ground_level +
                noise.GetNoise<float>(position.x + x, position.z + z) * ground_level * 0.2f;

            // The surface of the ground is filled with grass
            bool surface_level = false;
            for (int y = 0; y < size.y; y++) {
                if (position.y + y + 1 > noise_val) 
                    surface_level = true;
                if (position.y + y < noise_val)
                    blocks[PosToIdx(x, y, z)] = surface_level ? BLOCK_GRASS : BLOCK_DIRT;
                else
                    blocks[PosToIdx(x, y, z)] = BLOCK_AIR;
            }
        }
    }
}

void Chunk::Render() {
    if (!meshed) {
        mesh.Mesh(blocks, adjacents);
        meshed = true;
    }
    mesh.Render(position);
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
