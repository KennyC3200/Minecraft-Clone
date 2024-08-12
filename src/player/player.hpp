#pragma once

#include "../util/util.hpp"
#include "../gfx/window.hpp"
#include "../input/keyboard.hpp"
#include "../input/mouse.hpp"
#include "../world/world.hpp"
#include "camera.hpp"
#include "ray.hpp"

#define HOTBAR_SIZE 9

class Player {
public:
    void init(Window *window, Keyboard *keyboard, Mouse *mouse, World *world);
    void update();
    void render();

    Camera camera;
    Ray ray;

    float speed;

    glm::vec3 offset, position;
    glm::ivec3 chunk_position;

    int hotbar_idx;
    BlockID hotbar[HOTBAR_SIZE];
private:
    Window *window;
    Keyboard *keyboard;
    Mouse *mouse;
    World *world;
};
