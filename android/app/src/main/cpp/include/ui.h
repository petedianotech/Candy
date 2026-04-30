#pragma once

#include "config.h"
#include <string>

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