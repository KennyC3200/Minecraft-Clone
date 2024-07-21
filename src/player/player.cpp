#include "player.hpp"

void Player::init(Window *window, Keyboard *keyboard, Mouse *mouse, World *world) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->world = world;

    speed = 20.0f;

    camera.init(window, mouse);

    world_data.chunk_position = world->chunks_center;
}

void Player::update() {
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

    if (mouse->keys[GLFW_MOUSE_BUTTON_LEFT].pressed) {
        size_t idx = world->chunks_idx((int) game_data.chunk_position.x, (int) game_data.chunk_position.y, (int) game_data.chunk_position.z);
        world->chunks[idx]->data[CHUNK_POS_TO_IDX(8, 15, 8)] = BLOCK_AIR;
        world->chunks[idx]->meshed = false;
    }

    camera.update();

    game_data.position = {camera.position.x, camera.position.y, camera.position.z};
    game_data.chunk_position = world->chunks_center + game_data.position / 16.0f;

    world_data.position = {game_data.position.x, game_data.position.y, -game_data.position.z};
    world_data.chunk_position = world_data.position / 16.0f;
}

void Player::render() {
    ChunkMesh::shader.uniform_mat4("view", camera.view);
    ChunkMesh::shader.uniform_mat4("projection", camera.projection);
}
