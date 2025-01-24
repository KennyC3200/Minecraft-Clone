# Minecraft
This is a Minecraft clone, made with recreational intended purposes.

![Thumbnail Image](res/readme/thumbnail.png)

Building
-----
Currently, this is only tested for macOS. To build on macOS, run
```
make run
```
Which will build the executable file in the `bin` folder.

* Will in the future implement for CMake and Windows

Current Implemented Features
-----
Features that are implemented include:
* Movement
* Placing and blocks
* Removing blocks
* Hotbar

Libraries Used
-----
* [OpenGL](https://www.opengl.org/) graphics rendering
* [GLFW](https://www.glfw.org/) utility library for OpenGL
* [GLM](https://github.com/g-truc/glm) for OpenGL mathematics
* [imgui](https://github.com/ocornut/imgui) for GUI
* [stb image](https://github.com/nothings/stb/tree/master) for images

Issues and Fixes
-----
Path: `/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Carbon.framework/Headers/Carbon`

Update glfw path: `cmake -D CMAKE_OSX_SYSROOT=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk`

TODO
-----
* Like are vectors slow or something?
* Chunks rendering as player moves around
* Physics
* Padding issues, add `-Wpadded` to see
    * See [this article](http://www.catb.org/esr/structure-packing/#_who_should_read_this)
* HUD being rendered over by the blocks when hovering too close to block face
