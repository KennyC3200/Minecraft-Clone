#pragma once

#include "../util/util.h"
#include "../world/world.h"

struct RayCastData {
    bool hit;
    glm::ivec3 position, out;
};

class Ray {
public:
    void init(World *world, float max_distance);
    RayCastData cast(glm::vec3 position, glm::vec3 direction);

    float max_distance;
private:
    World *world;

    uint64_t *data;
};
