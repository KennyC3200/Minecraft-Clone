#pragma once

#include "../util/util.h"
#include "../gfx/window.h"
#include "../input/mouse.h"

class Camera {
public:
    void init(Window *window, Mouse *mouse, glm::ivec3 position);
    void update();

    void set_position(glm::vec3 &position);
    void set_toggled(bool toggled);

    glm::vec3 get_up();
    glm::vec3 get_right();
    glm::vec3 get_front();

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
