#ifndef CONFIG_H
#define CONFIG_H

#ifdef HEADLESS_MODE
    // Stub types and functions for headless builds
    
    struct Vector2 {
        float x, y;
    };
    
    struct Color {
        unsigned char r, g, b, a;
    };
    
    // Mouse button constants
    #define MOUSE_BUTTON_LEFT 0
    #define MOUSE_BUTTON_RIGHT 1
    #define MOUSE_BUTTON_MIDDLE 2
    
    // Key constants (simplified)
    #define KEY_SPACE 32
    #define KEY_P 80
    #define KEY_ESCAPE 27
    
    // Color constants
    constexpr Color RAYWHITE = {245, 245, 245, 255};
    constexpr Color DARKGRAY = {80, 80, 80, 255};
    constexpr Color LIGHTGRAY = {200, 200, 200, 255};
    constexpr Color WHITE = {255, 255, 255, 255};
    constexpr Color BLACK = {0, 0, 0, 255};
    constexpr Color RED = {255, 0, 0, 255};
    constexpr Color YELLOW = {255, 255, 0, 255};
    constexpr Color GREEN = {0, 255, 0, 255};
    constexpr Color BLUE = {0, 0, 255, 255};
    constexpr Color ORANGE = {255, 165, 0, 255};
    constexpr Color GOLD = {255, 215, 0, 255};
    constexpr Color LIME = {50, 205, 50, 255};
    constexpr Color LIGHTBLUE = {173, 216, 230, 255};
    constexpr Color CRIMSON = {220, 20, 60, 255};
    
    struct Font {
        int size;
    };
    
    struct Sound {
        int frameCount;
    };
    
    struct Music {
        int frameCount;
    };
    
    // Stub functions
    inline void InitWindow(int width, int height, const char* title) {}
    inline void InitAudioDevice() {}
    inline void CloseWindow() {}
    inline void CloseAudioDevice() {}
    inline bool WindowShouldClose() { return false; }
    inline void SetTargetFPS(int fps) {}
    inline float GetFrameTime() { return 0.016f; }
    inline Vector2 GetMousePosition() { return {0, 0}; }
    inline bool IsMouseButtonPressed(int button) { return false; }
    inline bool IsKeyPressed(int key) { return false; }
    
    inline void BeginDrawing() {}
    inline void EndDrawing() {}
    inline void ClearBackground(Color color) {}
    
    inline void DrawCircle(int x, int y, float radius, Color color) {}
    inline void DrawCircleLines(int x, int y, float radius, Color color) {}
    inline void DrawRectangle(int x, int y, int width, int height, Color color) {}
    inline void DrawRectangleLines(int x, int y, int width, int height, Color color) {}
    inline void DrawLineEx(Vector2 start, Vector2 end, float thick, Color color) {}
    inline void DrawLine(int x1, int y1, int x2, int y2, Color color) {}
    inline void DrawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color) {}
    inline void DrawText(const char* text, int x, int y, int fontSize, Color color) {}
    inline void DrawTextEx(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color tint) {}
    
    inline Font GetFontDefault() { return Font{20}; }
    inline Font LoadFont(const char* fileName) { return Font{20}; }
    inline Sound LoadSound(const char* fileName) { return Sound{0}; }
    inline Music LoadMusicStream(const char* fileName) { return Music{0}; }
    inline void UnloadSound(Sound sound) {}
    inline void UnloadMusicStream(Music music) {}
    inline void PlaySound(Sound sound) {}
    inline void PlayMusicStream(Music music) {}
    inline void StopMusicStream(Music music) {}
    inline void SetMusicVolume(Music music, float volume) {}
    inline void SetMasterVolume(float volume) {}

#else
    // Use Raylib in normal builds
    #include <raylib.h>
#endif

#endif // CONFIG_H
