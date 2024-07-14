#pragma once

#include "math.hpp"

enum Direction {
    NORTH = 0, // -z
    SOUTH = 1, // +z
    EAST  = 2, // +x
    WEST  = 3, // -x
    UP    = 4, // +y
    DOWN  = 5, // -y
};

namespace direction {
static constexpr glm::vec3 VECTOR[6] = {
    glm::vec3(0, 0, -1),
    glm::vec3(0, 0, 1),
    glm::vec3(1, 0, 0),
    glm::vec3(-1, 0, 0),
    glm::vec3(0, 1, 0),
    glm::vec3(0, -1, 0)
};
};
