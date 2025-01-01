#include "game.h"

int main() {
    Game game;
    game.Init();
    game.Loop();
    game.Destroy();
    return 0;
}
