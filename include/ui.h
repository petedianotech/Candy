<<<<<<< HEAD
#ifndef UI_H
#define UI_H
=======
#pragma once
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)

#include "config.h"
#include <string>

<<<<<<< HEAD
class UI {
public:
    UI();
    ~UI();
    
    void init();
    void update(float dt);
    void render(int score, int moves, int targetScore, int level, float levelTime);
    
    void showLevelComplete();
    void showGameOver();
    void showPause();
    
    bool isPaused() const { return paused; }
    void togglePause() { paused = !paused; }
    
private:
    Font mainFont;
    Font titleFont;
    
    bool paused = false;
    float popupAlpha = 0.0f;
    float popupScale = 0.5f;
    
    void drawScore(int score, int x, int y);
    void drawMoves(int moves, int x, int y);
    void drawLevel(int level, int x, int y);
    void drawTimer(float time, int x, int y);
    void drawProgressBar(int current, int target, int x, int y, int width, int height);
};

#endif // UI_H
=======
class Game;

class UI {
public:
    UI(Game* game);
    ~UI();

    void update(float deltaTime);
    void render();

    void showLevelComplete();
    void showGameOver();
    void showPauseMenu();

private:
    Game* game;

    void drawScore();
    void drawMoves();
    void drawLevel();
    void drawTimer();
    void drawProgressBar(float progress, int x, int y, int width, int height);
    void drawTextCentered(const std::string& text, int y, int fontSize, ColorA color);
};
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
