#pragma once

#include "math.h"

enum Direction : int {
    NORTH = 0, // -z
    SOUTH = 1, // +z
    EAST  = 2, // +x
    WEST  = 3, // -x
    UP    = 4, // +y
    DOWN  = 5, // -y
};

static const glm::vec3 VEC[6] = {
    glm::vec3( 0,  0, -1),
    glm::vec3( 0,  0,  1),
    glm::vec3( 1,  0,  0),
    glm::vec3(-1,  0,  0),
    glm::vec3( 0,  1,  0),
    glm::vec3( 0, -1,  0)
};

static const glm::ivec3 IVEC[6] = {
    glm::ivec3( 0,  0, -1),
    glm::ivec3( 0,  0,  1),
    glm::ivec3( 1,  0,  0),
    glm::ivec3(-1,  0,  0),
    glm::ivec3( 0,  1,  0),
    glm::ivec3( 0, -1,  0)
};
