# Minecraft
This is a Minecraft clone, made with recreational intended purposes.

![Thumbnail Image](res/readme/thumbnail.png)

Building
-----
The project is built using CMake. Run the following command to build
```
cd build && cmake --build .
```
This will create an executable `Minecraft`. Currently, only macOS is supported.

Current Implemented Features
-----
Features that are implemented include:
* Movement
* Placing and blocks
* Removing blocks
* Hotbar
* World generation

Libraries Used
-----
* [OpenGL](https://www.opengl.org/) graphics rendering
* [GLFW](https://www.glfw.org/) utility library for OpenGL
* [GLM](https://github.com/g-truc/glm) for OpenGL mathematics
* [imgui](https://github.com/ocornut/imgui) for GUI
* [stb image](https://github.com/nothings/stb/tree/master) for images

TODO
-----
* DO THEY NOT CACHE THE WORLD FOR GENERATION? MAYBE THATS WHAT I AM MISSING...
* Implement a ticks system
    * Chunks render at a tick rate
* dear imgui does not have a CMakeLists.txt file. Will most likely have to use a cmake/imgui.cmake file
    * SOLUTION: Put the CMakeLists.txt file in the lib/ directory instead, and compile all necessary
    libraries into a lib/liblib.a file (yes, the name is weird by default, but what can we do)
    * Same for glad, use a cmake/glad.cmake file
    * Still want to create the static library in build/lib/glad
* Multithread the chunks generation
    * Use a thread pool
* Physics
* Glass and leaves
* Trees
    * Transparent leafs
* Padding issues, add `-Wpadded` to see
    * See [this article](http://www.catb.org/esr/structure-packing/#_who_should_read_this)
* HUD being rendered over by the blocks when hovering too close to block face
* Fix cursor issue interacting with GUI even when off
* In the future, benchmark 1d array vs 2d array for chunks stored in the world
    * 2d array has cache misses
    * 1d array has a lot of multiplication calculations (costs a lot of cpu cycles)
