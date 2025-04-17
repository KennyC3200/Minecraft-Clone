#include "chunk_mesh.h"
#include "chunk.h"
#include "block_mesh.h"

Shader ChunkMesh::shader;

ChunkMesh::ChunkMesh() {
    vao.Init();
    vbo.Init(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    ibo.Init(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
}

ChunkMesh::~ChunkMesh() {
    vao.Destroy();
    vbo.Destroy();
    ibo.Destroy();
}

void ChunkMesh::Init() {
    shader.Init("../res/shaders/chunk.vert", "../res/shaders/chunk.frag");
}

void ChunkMesh::Mesh(Block blocks[], Chunk* adjacent_chunks[6]) {
    vertices.clear();
    indices.clear();

    for (int x = 0; x < Chunk::size.x; x++) {
        for (int y = 0; y < Chunk::size.y; y++) {
            for (int z = 0; z < Chunk::size.z; z++) {
                glm::ivec3 iter_pos = {x, y, z};

                BlockID block_ID = blocks[Chunk::PosToIdx(iter_pos)].GetID();
                if (block_ID == BLOCK_AIR) {
                    continue;
                }

                for (int i = 0; i < 6; i++) {
                    glm::ivec3 adjacent_pos = iter_pos + IVEC[i];

                    if (
                        adjacent_pos.x < 0 || adjacent_pos.x == Chunk::size.x ||
                        adjacent_pos.y < 0 || adjacent_pos.y == Chunk::size.y ||
                        adjacent_pos.z < 0 || adjacent_pos.z == Chunk::size.z
                    )
                    {
                        if (
                            (i == UP && adjacent_chunks[i] == nullptr) ||
                            (adjacent_chunks[i] != nullptr &&
                            adjacent_chunks[i]->GetBlock(
                                (adjacent_pos.x + Chunk::size.x) % Chunk::size.x,
                                (adjacent_pos.y + Chunk::size.y) % Chunk::size.y,
                                (adjacent_pos.z + Chunk::size.z) % Chunk::size.z
                            ).GetID() == BLOCK_AIR)
                        )
                        {
                            BlockMesh::Get(block_ID).MeshFace((Direction) i, iter_pos, vertices, indices);
                        }
                        continue;
                    }

                    if (blocks[Chunk::PosToIdx(adjacent_pos)].GetID() == BLOCK_AIR) {
                        BlockMesh::Get(block_ID).MeshFace((Direction) i, iter_pos, vertices, indices);
                    }
                }
            }
        }
    }
}

void ChunkMesh::Render(glm::ivec3& position) {
    // !!! VERY IMPORTANT !!!
    if (indices.empty()) {
        return;
    }

    ibo.Buffer(indices.size() * sizeof(uint32_t), &indices[0]);
    vbo.Buffer(vertices.size() * sizeof(uint32_t), &vertices[0]);

    // Bind the uniform vec3 for the chunk_pos in the vertex shader
    shader.UniformIVec3("chunk_pos", position);

    vao.AttribIPointer(vbo, 0, 1, GL_UNSIGNED_INT, 1 * sizeof(uint32_t), 0 * sizeof(uint32_t));

    vao.Bind();
    ibo.Bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
