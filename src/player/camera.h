#pragma once

#include "../util/util.h"
#include "../gfx/window.h"
#include "../input/mouse.h"

class Camera {
public:
    void init(Window *window, Mouse *mouse, glm::ivec3 position);
    void update();

    void set_position(glm::vec3 &position);
    glm::vec3 get_direction();

    glm::vec3 get_up();
    glm::vec3 get_right();
    glm::vec3 get_front();

    glm::mat4 get_view();
    glm::mat4 get_projection();

    void set_toggled(bool toggled);
private:
    Window *window;
    Mouse *mouse;

    glm::vec3 position;
    glm::vec3 direction;

    float yaw, pitch, roll;
    float fov;
    float z_near, z_far;
    float sensitivity;

    // Camera vectors that define the vector space
    glm::vec3 up, right, front;

    glm::mat4 view, projection;

    bool toggled;
};
