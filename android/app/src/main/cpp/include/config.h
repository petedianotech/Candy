#pragma once

#ifdef __ANDROID__
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "FruitBurst", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "FruitBurst", __VA_ARGS__))
#else
#define LOGI(...) printf(__VA_ARGS__)
#define LOGE(...) fprintf(stderr, __VA_ARGS__)
#endif

// Platform abstraction for graphics
#ifdef USE_RAYLIB
#include <raylib.h>
#define COLOR_WHITE WHITE
#define COLOR_BLACK BLACK
#define COLOR_RED RED
#define COLOR_GREEN GREEN
#define COLOR_BLUE BLUE
#define COLOR_YELLOW YELLOW
#define COLOR_ORANGE ORANGE
#define COLOR_PURPLE PURPLE
#define COLOR_PINK PINK
#define COLOR_GRAY GRAY

#define DrawTextA DrawText
#define DrawRectangleA DrawRectangle
#define DrawCircleA DrawCircle
#define DrawLineA DrawLine
#define MeasureTextA MeasureText
#define GetMouseX GetMouseX
#define GetMouseY GetMouseY
#define IsMouseButtonPressed IsMouseButtonPressed
#define IsMouseButtonDown IsMouseButtonDown
#define IsKeyPressed IsKeyPressed
#define GetFrameTime GetFrameTime
#define BeginDrawing BeginDrawing
#define EndDrawing EndDrawing
#define ClearBackground ClearBackground
#define SetTargetFPS SetTargetFPS
#define InitWindow InitWindow
#define WindowShouldClose WindowShouldClose
#define CloseWindow CloseWindow
#define GetScreenWidth GetScreenWidth
#define GetScreenHeight GetScreenHeight

typedef Color ColorA;
typedef Vector2 Vector2A;
typedef Rectangle RectangleA;

#elif defined(USE_SDL2)
// SDL2 stubs would go here
#else
// Headless mode stubs
struct Color { unsigned char r, g, b, a; };
struct Vector2 { float x, y; };
struct Rectangle { float x, y, width, height; };

#define COLOR_WHITE {255,255,255,255}
#define COLOR_BLACK {0,0,0,255}
#define COLOR_RED {255,0,0,255}
#define COLOR_GREEN {0,255,0,255}
#define COLOR_BLUE {0,0,255,255}
#define COLOR_YELLOW {255,255,0,255}
#define COLOR_ORANGE {255,165,0,255}
#define COLOR_PURPLE {128,0,128,255}
#define COLOR_PINK {255,192,203,255}
#define COLOR_GRAY {128,128,128,255}

inline void DrawTextA(const char*, int, int, int, Color) {}
inline void DrawRectangleA(int, int, int, int, Color) {}
inline void DrawCircleA(int, int, float, Color) {}
inline void DrawLineA(int, int, int, int, Color) {}
inline int MeasureTextA(const char*, int) { return 0; }
inline int GetMouseX() { return 0; }
inline int GetMouseY() { return 0; }
inline bool IsMouseButtonPressed(int) { return false; }
inline bool IsMouseButtonDown(int) { return false; }
inline bool IsKeyPressed(int) { return false; }
inline float GetFrameTime() { return 1.0f/60.0f; }
inline void BeginDrawing() {}
inline void EndDrawing() {}
inline void ClearBackground(Color) {}
inline void SetTargetFPS(int) {}
inline void InitWindow(int, int, const char*) {}
inline bool WindowShouldClose() { return false; }
inline void CloseWindow() {}
inline int GetScreenWidth() { return 800; }
inline int GetScreenHeight() { return 600; }

typedef Color ColorA;
typedef Vector2 Vector2A;
typedef Rectangle RectangleA;
#endif