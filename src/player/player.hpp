#pragma once

#include "../util/util.hpp"
#include "../gfx/window.hpp"
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"
#include "../world/world.hpp"
#include "camera.hpp"
#include "ray.hpp"

class Player {
public:
    void init(Window *window, Keyboard *keyboard, Mouse *mouse, World *world);
    void update();
    void render();

    Camera camera;
    Ray ray;

    // game block and chunk position
    glm::vec3 position;
    glm::vec3 chunk_position;

    // world chunk offset
    glm::vec3 chunk_offset;
private:
    Window *window;
    Keyboard *keyboard;
    Mouse *mouse;
    World *world;
};
