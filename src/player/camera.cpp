#include "camera.h"

void Camera::init(Window *window, Mouse *mouse, glm::ivec3 position) {
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

void Camera::update() {
    if (toggled) {
        yaw += sensitivity * mouse->get_position_delta().x;
        pitch += sensitivity * mouse->get_position_delta().y;
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
        (float) window->size.x / window->size.y,
        z_near, z_far);
}

void Camera::set_position(glm::vec3 &position) {
    this->position = position;
}

glm::vec3 Camera::get_direction() {
    return direction;
}

glm::vec3 Camera::get_up() {
    return up;
}

glm::vec3 Camera::get_right() {
    return right;
}

glm::vec3 Camera::get_front() {
    return front;
}

glm::mat4 Camera::get_view() {
    return view;
}

glm::mat4 Camera::get_projection() {
    return projection;
}

void Camera::set_toggled(bool toggled) {
    this->toggled = toggled;
}
