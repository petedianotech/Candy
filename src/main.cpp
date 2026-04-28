#ifdef HEADLESS_MODE
    #warning "Building without graphics library - this is a core game logic build only"
    #include <iostream>
    int main() {
        std::cout << "Fruit Burst Game - Headless Build\n";
        std::cout << "This build requires SDL2 or Raylib for graphics.\n\n";
        std::cout << "To enable graphics, install one of:\n";
        std::cout << "  - Raylib 4.5+\n";
        std::cout << "  - SDL2\n\n";
        std::cout << "On Ubuntu/Debian:\n";
        std::cout << "  sudo apt-get install libsdl2-dev\n\n";
        std::cout << "Or rebuild with Raylib support.\n";
        return 0;
    }
#else

#include <raylib.h>
#include "game.h"
#include <iostream>

int main() {
    // Initialize window
    const int screenWidth = 900;
    const int screenHeight = 1200;
    
    InitWindow(screenWidth, screenHeight, "Fruit Burst - Match 3 Game");
    InitAudioDevice();
    
    SetTargetFPS(60);
    
    try {
        // Create and initialize game
        Game game;
        game.init();
        
        // Main game loop
        while (!WindowShouldClose() && game.isRunning()) {
            float dt = GetFrameTime();
            
            // Update
            game.update(dt);
            
            // Render
            BeginDrawing();
            ClearBackground(RAYWHITE);
            game.render();
            EndDrawing();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    // Cleanup
    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}

#endif
