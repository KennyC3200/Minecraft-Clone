#pragma once

#include "../util/util.h"
#include "../world/world.h"

struct RaycastData {
    bool hit;
    glm::ivec3 position, out;
};

RaycastData Raycast(World* world, glm::vec3 position, glm::vec3 direction, float max_distance);
