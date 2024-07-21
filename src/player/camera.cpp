#include "camera.hpp"

void Camera::init(Window *window, Mouse *mouse) {
    this->window = window;
    this->mouse = mouse;

    position = glm::vec3(0.0f, 0.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    // position = glm::vec3(0.0f, 0.0f, 3.0f);
    // target = glm::vec3(0.0f, 0.0f, 0.0f);
    // direction = glm::normalize(position - target);
    //
    // right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
    // up = glm::cross(direction, right);

    // point towards -Z axis
    yaw = -90.0f;
    pitch = 0.0f;
    roll = 0.0f;

    fov = 45.0f;
    z_near = 0.1f;
    z_far = 1000.0f;
    sensitivity = 0.1f;

    toggled = true;
}

void Camera::update() {
    if (toggled) {
        yaw += sensitivity * mouse->position_delta.x;
        pitch += sensitivity * mouse->position_delta.y;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(direction);
        pitch = CLAMP(pitch, -89.0f, 89.0f);
        right = glm::normalize(glm::cross(front, up));

        // this is the cross product of the up vector and right vector
        // gives the direction that the player will move in the x and z components
        direction = glm::normalize(glm::cross(up, right));
    }

    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(
        glm::radians(fov), 
        (float) window->size.x / window->size.y,
        z_near, z_far);
}
