#include "player.hpp"

void Player::init(Window *window, Keyboard *keyboard, Mouse *mouse, World *world) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->world = world;

    camera.init(window, mouse);

    chunk_offset = world->chunks_center;
}

void Player::update() {
    // handle movement
    if (keyboard->keys[GLFW_KEY_W].down) {
        camera.position += 60.0f * (float) window->time_delta * camera.front;
    }
    if (keyboard->keys[GLFW_KEY_S].down) {
        camera.position -= 60.0f * (float) window->time_delta * camera.front;
    }
    if (keyboard->keys[GLFW_KEY_A].down) {
        camera.position -= 60.0f * (float) window->time_delta * glm::normalize(glm::cross(camera.front, camera.up));
    }
    if (keyboard->keys[GLFW_KEY_D].down) {
        camera.position += 60.0f * (float) window->time_delta * glm::normalize(glm::cross(camera.front, camera.up));
    }
    camera.update();

    position = {camera.position.x, camera.position.y, -camera.position.z};
    chunk_position = position / 16.0f;
    chunk_offset = world->chunks_center + chunk_position;
}

void Player::render() {
    ChunkMesh::shader.uniform_mat4("view", camera.view);
    ChunkMesh::shader.uniform_mat4("projection", camera.projection);
}
