# Minecraft

# TODO
- Optimize
    - Instanced rendering: instead of rendering a quad at a time, we could've also batched all the quads we want to render and then, with an instanced renderer, 
      render all the batched sprites with just a single draw call. This is relatively easy to do since each sprite is composed of the same vertices, but differs in 
      only a model matrix; something that we can easily include in an instanced array. This allows OpenGL to render a lot more sprites per frame. 
      Instanced rendering can also be used to render particles and/or characters glyphs.
    - Minimize state changes: state changes (like binding textures or switching shaders) are generally quite expensive in OpenGL, so you want to avoid doing a 
      large amount of state changes. One approach to minimize state changes is to create your own state manager that stores the current value of an OpenGL state 
      (like which texture is bound) and only switch if this value needs to change; this prevents unnecessary state changes. Another approach is to sort all the 
      renderable objects by state change: first render all the objects with shader one, then all objects with shader two, and so on; this can of course be extended 
      to blend state changes, texture binds, framebuffer switches etc.

    - Don't render chunk border faces
        - Pass in pointers to surrounding chunk data (uint64_t* or nullptr for chunks that aren't loaded)
    - Refactor code
    - Batch render the chunks
        - How do I pass in the model matrix?
        - Have different buffers to batch render: `DATA`, `INDICES`, defined as TEMPLATES
            ```cpp
            template<typename T>
            struct ChunkMeshBuffer {
                T *data;
                
                // data for this buffer, nullptr if not allocated
                size_t capacity;

                // current index (in bytes) into data
                size_t index;

                // final count (in bytes) in data
                size_t count;

                // current count (in elements) of data
                size_t elements;
            };
            ```
    - Minimize state changes
    - Cannot have `BLOCK_AIR`? Solution: need to have `TRANSPARENT` or `OPAQUE` value in the metadata
- Fix camera snapping
