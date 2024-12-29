#include "mouse.h"

glm::vec2 Mouse::get_position() {
    return position;
}

glm::vec2 Mouse::get_position_delta() {
    return position_delta;
}
