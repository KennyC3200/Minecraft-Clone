# Minecraft

# TODO
1. Create `vertex_buffer` (think of a better name for this) and `uv_buffer`
2. In the `BlockMesh` class, create a `uv_coordinates` array
3. Then, in the chunk mesh, simply bind `BlockMesh::BLOCK_VERTICES` and `mesh.uv_coordinates` and then have the `std::vector<float> indices` vector choose which
   faces to render
