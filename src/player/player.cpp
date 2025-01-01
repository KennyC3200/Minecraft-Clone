#include "player.h"

void Player::Init(Window* window, Keyboard* keyboard, Mouse* mouse, World* world) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->world = world;

    speed = 15.0f;

    std::fill(hotbar, hotbar + Player::hotbar_size, BLOCK_NONE);
    hotbar[0] = BLOCK_DIRT;
    hotbar[1] = BLOCK_GRASS;
    hotbar[2] = BLOCK_STONE;
    hotbar[3] = BLOCK_SAND;
    hotbar[4] = BLOCK_LOG;
    hotbar[5] = BLOCK_PLANK;
    current_hotbar_idx = 0;

    float player_height = 1.8f;
    offset = {
        0.001f + (int)(world->GetChunksSize().x * Chunk::size.x / 2), 
        0.001f + (int)(world->GetChunksSize().y * Chunk::size.y / 2) + player_height, 
        0.001f + (int)(world->GetChunksSize().z * Chunk::size.z / 2)
    };
    position = offset;

    camera.Init(window, mouse, offset);
    ray.Init(this->world, 8.0f);
}

/* Update the player 
 * Handle movement
 * Update camera
 * Handle block placement/deletion
 * */
void Player::Update() {
    float displacement = speed * window->time_delta;
    if (keyboard->GetButton(GLFW_KEY_W).down) {
        position += displacement * camera.GetFront();
    }
    if (keyboard->GetButton(GLFW_KEY_S).down) {
        position -= displacement * camera.GetFront();
    }
    if (keyboard->GetButton(GLFW_KEY_A).down) {
        position -= displacement * camera.GetRight();
    }
    if (keyboard->GetButton(GLFW_KEY_D).down) {
        position += displacement * camera.GetRight();
    }
    if (keyboard->GetButton(GLFW_KEY_SPACE).down) {
        position.y += 0.5f * displacement;
    }
    if (keyboard->GetButton(GLFW_KEY_LEFT_SHIFT).down) {
        position.y -= 0.5f * displacement;
    }

    // Update the camera
    camera.SetPosition(position);
    camera.Update();

    // Handle the hotbar
    // Keep in mind the index starts at 0, not 
    for (int i = 0; i < Player::hotbar_size; i++) {
        if (keyboard->GetButton(GLFW_KEY_1 + i).pressed) {
            current_hotbar_idx = i;
        }
    }

    // Handle block placement/deletion
    RayCastData raycast = ray.Cast(position, camera.GetDirection());
    if (raycast.hit) {
        if (mouse->GetButton(GLFW_MOUSE_BUTTON_LEFT).pressed) {
            world->GetBlock(raycast.position)->SetID(BLOCK_AIR);
            world->GetChunk(raycast.position)->SetDirty();
        }
        if (mouse->GetButton(GLFW_MOUSE_BUTTON_RIGHT).pressed) {
            glm::vec3 block_position = raycast.position + raycast.out;
            Block *block = world->GetBlock(block_position);

            if (block != nullptr && block->GetID() == BLOCK_AIR) {
                world->GetBlock(block_position)->SetID(hotbar[current_hotbar_idx]);
                world->GetChunk(block_position)->SetDirty();
            }
        }
    }
}

Camera& Player::GetCamera() {
    return camera;
}
