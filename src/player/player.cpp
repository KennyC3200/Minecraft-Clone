#include "player.h"
#include "ray.h"
#include "../ui/hud/hud_manager.h"
#include "../world/chunk.h"

void Player::Init(Window* window, Keyboard* keyboard, Mouse* mouse, World* world) {
    this->window = window;
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->world = world;

    speed = 50.0f;

    std::fill(hotbar, hotbar + Player::hotbar_size, BLOCK_NONE);
    hotbar[0] = BLOCK_DIRT;
    hotbar[1] = BLOCK_GRASS;
    hotbar[2] = BLOCK_STONE;
    hotbar[3] = BLOCK_SAND;
    hotbar[4] = BLOCK_LOG;
    hotbar[5] = BLOCK_PLANK;
    hotbar_idx = 0;

    height = 1.8f;
    offset = {
        0.001f + (int)(world->GetChunksSize().x * Chunk::size.x / 2),
        0.001f + (int)(world->GetChunksSize().y * Chunk::size.y / 2) + height,
        0.001f + (int)(world->GetChunksSize().z * Chunk::size.z / 2)
    };

    position = offset;
    chunk_position = {
        (int)(position.x / Chunk::size.x),
        (int)(position.y / Chunk::size.y),
        (int)(position.z / Chunk::size.z)};
    chunk_position_prev = chunk_position;

    camera.Init(window, mouse, offset);
}

void Player::Update() {
    float displacement = speed * window->GetTimeDelta();
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
    camera.SetPosition({position.x, position.y + height, position.z});
    camera.Update();

    // Calculate new chunk position
    chunk_position = {
        (int)(position.x / Chunk::size.x),
        (int)(position.y / Chunk::size.y),
        (int)(position.z / Chunk::size.z)};

    // Generate new chunks when moving between chunks
    int x_diff = chunk_position.x - chunk_position_prev.x;
    int z_diff = chunk_position.z - chunk_position_prev.z;
    if (x_diff != 0 || z_diff != 0) {
        if (x_diff > 0) {
            world->GenerateChunks(EAST);
        } else if (x_diff < 0) {
            world->GenerateChunks(WEST);
        } else if (z_diff > 0) {
            world->GenerateChunks(SOUTH);
        } else if (z_diff < 0) {
            world->GenerateChunks(NORTH);
        }

        chunk_position_prev.x = chunk_position.x;
        chunk_position_prev.y = chunk_position.y;
        chunk_position_prev.z = chunk_position.z;
    }

    // Handle the hotbar. Keep in mind the index starts at 0, not 1
    for (int i = 0; i < Player::hotbar_size; i++) {
        if (keyboard->GetButton(GLFW_KEY_1 + i).pressed) {
            hotbar_idx = i;
            HudManager::MeshHotbar();
        }
    }

    // Handle block placement/deletion
    RaycastData raycast = Raycast(world, camera.GetPosition(), camera.GetDirection(), 8.0f);
    if (raycast.hit) {
        if (mouse->GetButton(GLFW_MOUSE_BUTTON_LEFT).pressed) {
            world->GetBlock(raycast.position)->SetID(BLOCK_AIR);
            world->GetChunk(raycast.position)->SetDirty();
        }
        if (mouse->GetButton(GLFW_MOUSE_BUTTON_RIGHT).pressed) {
            glm::vec3 block_position = raycast.position + raycast.out;
            Block* block = world->GetBlock(block_position);

            if (block != nullptr && block->GetID() == BLOCK_AIR) {
                block->SetID(hotbar[hotbar_idx]);
                world->GetChunk(block_position)->SetDirty();
            }
        }
    }
}

BlockID Player::GetHotbarItem(int idx) {
    return hotbar[idx];
}

int Player::GetHotbarIdx() {
    return hotbar_idx;
}
