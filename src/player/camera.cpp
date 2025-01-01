#include "camera.h"

void Camera::Init(Window* window, Mouse* mouse, glm::ivec3 position) {
    this->window = window;
    this->mouse = mouse;
    this->position = position;

    direction = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    // point towards -Z axis
    yaw = -90.0f;
    pitch = 0.0f;
    roll = 0.0f;

    fov = 60.0f;
    z_near = 0.1f;
    z_far = 1000.0f;
    sensitivity = 0.1f;

    toggled = true;
}

void Camera::Update() {
    if (toggled) {
        yaw += sensitivity * mouse->GetPositionDelta().x;
        pitch += sensitivity * mouse->GetPositionDelta().y;
        pitch = CLAMP(pitch, -89.0f, 89.0f);

        direction = glm::normalize(glm::vec3(
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        ));

        right = glm::normalize(glm::cross(direction, up));

        /* This is the cross product of the up vector and right vector 
         * gives the direction that the player will move in the x and z components 
         * */
        front = glm::normalize(glm::cross(up, right));
    }

    view = glm::lookAt(position, position + direction, up);
    projection = glm::perspective(
        glm::radians(fov), 
        (float) window->GetSize().x / window->GetSize().y,
        z_near, z_far);
}

void Camera::SetPosition(glm::vec3& position) {
    this->position = position;
}

glm::vec3 Camera::GetDirection() {
    return direction;
}

glm::vec3 Camera::GetUp() {
    return up;
}

glm::vec3 Camera::GetRight() {
    return right;
}

glm::vec3 Camera::GetFront() {
    return front;
}

glm::mat4 Camera::GetView() {
    return view;
}

glm::mat4 Camera::GetProjection() {
    return projection;
}

void Camera::SetToggled(bool toggled) {
    this->toggled = toggled;
}
