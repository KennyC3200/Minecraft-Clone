# Minecraft

# TODO
- Problem: each face has different vertex coordinates
    - Since we are rendering one face at a time, we need to determine which face it is, then specify the corresponding vertex buffer. Preferably, this would be in
      the BlockMesh class as a static array
    - Need to have [different buffers](https://stackoverflow.com/questions/8757212/opengles-2-0-separate-buffers-for-vertices-colors-and-texture-coordinates) for the ChunkMesh?
- Render multiple faces
    - Each face is described by `BlockMesh::VERTICES[]`: `BlockMesh::VERTICES[UP]`, `BlockMesh::VERTICES[DOWN]`, etc.
    - Then, we need to have those vertices somehow work with the BlockMesh texture UV's
