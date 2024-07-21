#include "player.hpp"

void Player::init(Window *window, Keyboard *keyboard, Mouse *mouse, World *world) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->world = world;

    speed = 20.0f;

    camera.init(window, mouse);

    chunk_offset = world->chunks_center;
    world
        ->chunks[world->chunks_idx((int) chunk_offset.x, (int) chunk_offset.y, (int) chunk_offset.z)]
        ->data[CHUNK_POS_TO_IDX(8, 15, 8)] = BLOCK_AIR;
}

void Player::update() {
    // handle movement
    if (keyboard->keys[GLFW_KEY_W].down) {
        camera.position += speed * (float) window->time_delta * camera.direction;
    }
    if (keyboard->keys[GLFW_KEY_S].down) {
        camera.position -= speed * (float) window->time_delta * camera.direction;
    }
    if (keyboard->keys[GLFW_KEY_A].down) {
        camera.position -= speed * (float) window->time_delta * camera.right;
    }
    if (keyboard->keys[GLFW_KEY_D].down) {
        camera.position += speed * (float) window->time_delta * camera.right;
    }
    if (keyboard->keys[GLFW_KEY_SPACE].down) {
        camera.position.y += speed * (float) window->time_delta;
    }
    if (keyboard->keys[GLFW_KEY_LEFT_SHIFT].down) {
        camera.position.y -= speed * (float) window->time_delta;
    }
    camera.update();

    position = {camera.position.x, camera.position.y, camera.position.z};
    chunk_position = position / 16.0f;
    chunk_offset = world->chunks_center + chunk_position;
}

void Player::render() {
    ChunkMesh::shader.uniform_mat4("view", camera.view);
    ChunkMesh::shader.uniform_mat4("projection", camera.projection);
}
