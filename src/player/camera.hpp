#pragma once

#include "../util/util.hpp"
#include "../gfx/window.hpp"
#include "../input/mouse.hpp"

class Camera {
public:
    void init(Window *window, Mouse *mouse, glm::ivec3 position);
    void update();

    glm::vec3 position;
    glm::vec3 direction;

    // camera vectors that define the vector space
    glm::vec3 up, right, front;

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
