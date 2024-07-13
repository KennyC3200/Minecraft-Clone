#pragma once

#include "../util/util.hpp"
#include "camera.hpp"

class Player {
public:
    void init();
    void destroy();
    void update();
    void render();

    glm::vec2 position;
};
