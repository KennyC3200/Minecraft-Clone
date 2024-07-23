#pragma once

#include "../util/util.hpp"

struct RayCastData {
    bool hit;
    glm::vec<3, size_t> position;
};

class Ray {
public:
    void init(float max_distance, glm::vec<3, size_t> data_size);
    void update(uint64_t *data, glm::vec3 position, glm::vec3 direction);
    RayCastData cast();

    glm::vec3 position;
    glm::vec3 direction;
    float max_distance;

    RayCastData tmp;
private:
    uint64_t *data;
    glm::vec<3, size_t> data_size;
};
