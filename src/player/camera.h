#pragma once

#include "../gfx/window.h"
#include "../input/mouse.h"

class Camera {
public:
    void Init(Window* window, Mouse* mouse, glm::ivec3 position);
    void Update();

    inline void SetToggled(bool toggled) { this->toggled = toggled; }
    inline glm::vec3 GetPosition() { return position; }
    inline void SetPosition(glm::vec3 position) { this->position = position; }
    inline glm::vec3 GetDirection() { return direction; }
    inline glm::vec3 GetUp() { return up; }
    inline glm::vec3 GetRight() { return right; }
    inline glm::vec3 GetFront() { return front; }
    inline glm::mat4& GetModel() { return model; }
    inline glm::mat4& GetView() { return view; }
    inline glm::mat4& GetProjection() { return projection; }
    inline glm::mat4& GetMVP() { return mvp; }

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

    glm::mat4 model, view, projection;
    glm::mat4 mvp;

    bool toggled;
};
