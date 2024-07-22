#pragma once

#include "../util/util.hpp"

struct RayCastData {
    bool hit;
    glm::vec<3, size_t> position;
};

class Ray {
public:
    void init(uint64_t **data, float max_distance);
    void update(glm::vec3 position, glm::vec3 direction);
    RayCastData cast();

    glm::vec3 position;
    glm::vec3 direction;
    float max_distance;
private:
    uint64_t **data;
};
