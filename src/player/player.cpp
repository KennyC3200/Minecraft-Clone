#include "player.hpp"

void Player::init(Window *window, Keyboard *keyboard, Mouse *mouse) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;

    camera.init(window, mouse);
}

void Player::update() {
    // handle movement
    if (keyboard->keys[GLFW_KEY_W].down) {
        camera.position += 30.0f * (float) window->time_delta * camera.front;
    }
    if (keyboard->keys[GLFW_KEY_S].down) {
        camera.position -= 30.0f * (float) window->time_delta * camera.front;
    }
    if (keyboard->keys[GLFW_KEY_A].down) {
        camera.position -= 30.0f * (float) window->time_delta * glm::normalize(glm::cross(camera.front, camera.up));
    }
    if (keyboard->keys[GLFW_KEY_D].down) {
        camera.position += 30.0f * (float) window->time_delta * glm::normalize(glm::cross(camera.front, camera.up));
    }

    camera.update();
}

void Player::render() {
    // TODO: implement third-person
    ChunkMesh::shader.uniform_mat4("view", camera.view);
    ChunkMesh::shader.uniform_mat4("projection", camera.projection);
}
