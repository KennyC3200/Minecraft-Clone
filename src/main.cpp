#include "game.hpp"

int main() {
    Game game;
    game.init();
    game.loop();
    game.destroy();
    return 0;
}
