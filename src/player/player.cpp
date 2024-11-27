#include "player.hpp"

void Player::init(Window *window, Keyboard *keyboard, Mouse *mouse, World *world) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->world = world;

    speed = 15.0f;

    for (int i = 0; i < HOTBAR_SIZE; i++) {
        hotbar[i] = BLOCK_NONE;
    }
    hotbar[0] = BLOCK_DIRT;
    hotbar[1] = BLOCK_GRASS;
    hotbar[2] = BLOCK_STONE;
    hotbar[3] = BLOCK_SAND;
    hotbar[4] = BLOCK_LOG;
    hotbar[5] = BLOCK_PLANK;
    hotbar_idx = 0;

    int player_height = 2;
    offset = {
        CHUNK_SIZE_X * world->chunks_size.x / 2, 
        CHUNK_SIZE_Y * world->ground_level + player_height, 
        CHUNK_SIZE_Z * world->chunks_size.z / 2};
    offset += 0.0001;
    position = {0, 0, 0};

    camera.init(window, mouse, offset);
    ray.init(this->world, 8.0f);
}

void Player::update() {
    glm::vec3 displacement;
    float _displacement;
    if (keyboard->keys[GLFW_KEY_W].down) {
        displacement = speed * (float) window->time_delta * camera.front;
        camera.position += displacement;
        position += displacement;
    }
    if (keyboard->keys[GLFW_KEY_S].down) {
        displacement = speed * (float) window->time_delta * camera.front;
        camera.position -= displacement;
        position -= displacement;
    }
    if (keyboard->keys[GLFW_KEY_A].down) {
        displacement = speed * (float) window->time_delta * camera.right;
        camera.position -= displacement;
        position -= displacement;
    }
    if (keyboard->keys[GLFW_KEY_D].down) {
        displacement = speed * (float) window->time_delta * camera.right;
        camera.position += displacement;
        position += displacement;
    }
    if (keyboard->keys[GLFW_KEY_SPACE].down) {
        _displacement = speed * (float) window->time_delta;
        camera.position.y += _displacement;
        position.y += _displacement;
    }
    if (keyboard->keys[GLFW_KEY_LEFT_SHIFT].down) {
        _displacement = speed * (float) window->time_delta; 
        camera.position.y -= _displacement;
        position.y -= _displacement;
    }
    for (int i = 0; i < HOTBAR_SIZE; i++) {
        if (keyboard->keys[GLFW_KEY_1 + i].pressed) {
            hotbar_idx = i;
        }
    }

    chunk_position = glm::ivec3(position + offset);

    if (mouse->keys[GLFW_MOUSE_BUTTON_LEFT].pressed) {
        RayCastData raycast = ray.cast(position + offset, camera.direction);
        if (raycast.hit) {
            Block *block = world->block_get(raycast.position);
            block->set_id(BLOCK_AIR);
            Chunk *chunk = world->chunk_get(raycast.position);
            chunk->meshed = false;
            for (int i = 0; i < 6; i++) {
                if (chunk->neighbors[i]) {
                    chunk->neighbors[i]->meshed = false;
                }
            }
        }
    }

    if (mouse->keys[GLFW_MOUSE_BUTTON_RIGHT].pressed) {
        RayCastData raycast = ray.cast(position + offset, camera.direction);
        if (raycast.hit && world->block_get(raycast.position + raycast.out) && hotbar[hotbar_idx] != BLOCK_NONE) {
            glm::ivec3 _position = raycast.position + raycast.out;
            Block *block = world->block_get(_position);
            block->set_id(hotbar[hotbar_idx]);
            Chunk *chunk = world->chunk_get(_position);
            chunk->meshed = false;
            for (int i = 0; i < 6; i++) {
                if (chunk->neighbors[i]) {
                    chunk->neighbors[i]->meshed = false;
                }
            }
        }
    }

    camera.update();
}

void Player::render() {
    ChunkMesh::shader.uniform_mat4("view", camera.view);
    ChunkMesh::shader.uniform_mat4("projection", camera.projection);
}
