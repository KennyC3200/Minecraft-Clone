#pragma once

#include "../util/util.hpp"
#include "../gfx/window.hpp"
#include "../input/mouse.hpp"

class Camera {
public:
    void init(Window *window, Mouse *mouse, glm::ivec3 position);
    void update();

    glm::vec3 position;
    glm::vec3 front, target, direction;
    glm::vec3 up, right;

    glm::mat4 view, projection;

    float yaw, pitch, roll;
    float fov;
    float z_near, z_far;
    float sensitivity;

    bool toggled;
private:
    Window *window;
    Mouse *mouse;
};
