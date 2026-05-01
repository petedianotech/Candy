#include "game.h"
#include "config.h"

int main() {
    // Initialize graphics if available
#ifdef USE_RAYLIB
    InitWindow(800, 600, "Fruit Burst Game");
    SetTargetFPS(60);
#endif

    Game game;
    game.run();

#ifdef USE_RAYLIB
    CloseWindow();
#endif

    return 0;
}