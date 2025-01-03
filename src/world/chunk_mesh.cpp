#include "chunk_mesh.h"
#include "chunk.h"

Shader ChunkMesh::shader;

ChunkMesh::ChunkMesh() {
    vao.Init();
    vbo.Init(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    ibo.Init(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
}

ChunkMesh::~ChunkMesh() {
    vao.Destroy();
    vbo.Destroy();
    ibo.Destroy();
}

void ChunkMesh::Init() {
    shader.Init("res/shaders/chunk.vs", "res/shaders/chunk.fs");
}

void ChunkMesh::Mesh(Block blocks[], glm::ivec3 position, Chunk* adjacent_chunks[6]) {
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

                glm::ivec3 block_pos = position + iter_pos;
                for (int i = 0; i < 6; i++) {
                    glm::ivec3 adjacent_pos = iter_pos + mc::IVEC[i];

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
                            BlockMesh::Get(block_ID).MeshFace((Direction) i, block_pos, vertices, indices);
                        }
                        continue;
                    }

                    if (blocks[Chunk::PosToIdx(adjacent_pos)].GetID() == BLOCK_AIR) {
                        BlockMesh::Get(block_ID).MeshFace((Direction) i, block_pos, vertices, indices);
                    }
                }
            }
        }
    }
}

void ChunkMesh::Render() {
    ibo.Buffer(indices.size() * sizeof(unsigned int), &indices[0]);
    vbo.Buffer(vertices.size() * sizeof(float), &vertices[0]);

    vao.AttribPointer(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0 * sizeof(float));
    vao.AttribPointer(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

    vao.Bind();
    ibo.Bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}
