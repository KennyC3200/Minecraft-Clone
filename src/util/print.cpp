#include "print.h"

std::string Vec3fToString(glm::vec3 vec) {
    return "(" + std::to_string(vec.x) + "," + std::to_string(vec.y) + "," + std::to_string(vec.z) + ")";
}

std::string Vec2iToString(glm::ivec2 vec) {
    return "(" + std::to_string(vec.x) + "," + std::to_string(vec.y) + ")";
}

std::string Vec3iToString(glm::ivec3 vec) {
    return "(" + std::to_string(vec.x) + "," + std::to_string(vec.y) + "," + std::to_string(vec.z) + ")";
}
