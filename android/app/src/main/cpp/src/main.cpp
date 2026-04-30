#include "game.h"
#include "config.h"

#ifdef __ANDROID__
#include <android_native_app_glue.h>
#include <android/log.h>

void android_main(struct android_app* app) {
    // Initialize Android app
    app_dummy();

    // Initialize graphics if available
#ifdef USE_RAYLIB
    // Raylib handles Android initialization
#endif

    Game game;
    game.run();

#ifdef USE_RAYLIB
    // Raylib handles cleanup
#endif
}
#else
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
#endif