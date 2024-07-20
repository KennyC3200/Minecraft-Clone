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

    glm::vec3 position;
    Camera camera;
    Ray ray;
private:
    Window *window;
    Keyboard *keyboard;
    Mouse *mouse;
    World *world;
};
