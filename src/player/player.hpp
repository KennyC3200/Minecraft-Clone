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

    float speed;

    glm::ivec3 offset;
    glm::vec3 position;
private:
    Window *window;
    Keyboard *keyboard;
    Mouse *mouse;
    World *world;
};
