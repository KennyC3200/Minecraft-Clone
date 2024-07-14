# Minecraft

# TODO
- Have separate buffers for the ChunkMesh: DATA, INDICES, FACES
    - Let the ChunkMesh and BlockMesh communicate with each other
- Render multiple faces
    - Each face is described by `BlockMesh::VERTICES[]`: `BlockMesh::VERTICES[UP]`, `BlockMesh::VERTICES[DOWN]`, etc.
    - Then, we need to have those vertices somehow work with the BlockMesh texture UV's
