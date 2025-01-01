#pragma once

#include "../util/util.h"
#include "../gfx/window.h"
#include "../input/mouse.h"

class Camera {
public:
    void Init(Window* window, Mouse* mouse, glm::ivec3 position);
    void Update();

    void SetPosition(glm::vec3& position);
    glm::vec3 GetDirection();

    glm::vec3 GetUp();
    glm::vec3 GetRight();
    glm::vec3 GetFront();

    glm::mat4 GetView();
    glm::mat4 GetProjection();

    void SetToggled(bool toggled);

private:
    Window* window;
    Mouse* mouse;

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
