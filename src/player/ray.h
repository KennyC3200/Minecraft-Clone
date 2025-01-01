#pragma once

#include "../util/util.h"
#include "../world/world.h"

struct RayCastData {
    bool hit;
    glm::ivec3 position, out;
};

class Ray {
public:
    void Init(World *world, float max_distance);
    RayCastData Cast(glm::vec3 position, glm::vec3 direction);

    float max_distance;

private:
    World *world;

    uint64_t *data;
};
