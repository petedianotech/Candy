#include "ui.h"
<<<<<<< HEAD
#include <cmath>
#include <sstream>
#include <iomanip>

UI::UI() : mainFont({0}), titleFont({0}) {
}

UI::~UI() {
}

void UI::init() {
    // Load fonts (using default font if custom not available)
    mainFont = GetFontDefault();
    titleFont = GetFontDefault();
}

void UI::update(float dt) {
}

void UI::render(int score, int moves, int targetScore, int level, float levelTime) {
    // Header background
    DrawRectangle(0, 0, 900, 130, {45, 45, 120, 255});
    
    // Title
    DrawText("Fruit Burst", 350, 10, 40, YELLOW);
    
    // Stats row 1
    drawScore(score, 50, 70);
    drawLevel(level, 350, 70);
    drawMoves(moves, 650, 70);
    
    // Timer and progress
    drawTimer(levelTime, 50, 105);
    drawProgressBar(score, targetScore, 350, 105, 200, 15);
}

void UI::drawScore(int score, int x, int y) {
    DrawText("SCORE", x, y, 16, WHITE);
    
    std::ostringstream oss;
    oss << score;
    DrawText(oss.str().c_str(), x, y + 20, 28, YELLOW);
}

void UI::drawMoves(int moves, int x, int y) {
    DrawText("MOVES", x, y, 16, WHITE);
    
    std::ostringstream oss;
    oss << moves;
    std::string movesStr = oss.str();
    
    Color moveColor = moves > 5 ? LIME : (moves > 0 ? YELLOW : RED);
    DrawText(movesStr.c_str(), x, y + 20, 28, moveColor);
}

void UI::drawLevel(int level, int x, int y) {
    DrawText("LEVEL", x, y, 16, WHITE);
    
    std::ostringstream oss;
    oss << level;
    DrawText(oss.str().c_str(), x, y + 20, 28, LIGHTBLUE);
}

void UI::drawTimer(float time, int x, int y) {
    int minutes = (int)time / 60;
    int seconds = (int)time % 60;
    
    char timeStr[10];
    sprintf(timeStr, "%02d:%02d", minutes, seconds);
    
    DrawText("TIME", x, y, 14, WHITE);
    DrawText(timeStr, x, y + 15, 20, YELLOW);
}

void UI::drawProgressBar(int current, int target, int x, int y, int width, int height) {
    // Background
    DrawRectangle(x, y, width, height, DARKGRAY);
    
    // Fill
    if (target > 0) {
        int fillWidth = (int)((float)current / target * width);
        fillWidth = std::min(fillWidth, width);
        
        Color fillColor = current >= target ? GREEN : ORANGE;
        DrawRectangle(x, y, fillWidth, height, fillColor);
    }
    
    // Border
    DrawRectangleLines(x, y, width, height, WHITE);
    
    // Text
    std::ostringstream oss;
    oss << current << "/" << target;
    DrawText(oss.str().c_str(), x + 5, y - 20, 12, WHITE);
}

void UI::showLevelComplete() {
    // Draw semi-transparent overlay
    DrawRectangle(0, 0, 900, 1200, {0, 0, 0, 180});
    
    // Draw popup
    DrawRectangle(300, 450, 300, 200, {50, 200, 50, 255});
    DrawRectangleLines(300, 450, 300, 200, GOLD);
    
    DrawText("LEVEL COMPLETE!", 320, 480, 20, YELLOW);
    DrawText("Press SPACE to continue", 320, 540, 16, WHITE);
}

void UI::showGameOver() {
    // Draw semi-transparent overlay
    DrawRectangle(0, 0, 900, 1200, {0, 0, 0, 200});
    
    // Draw popup
    DrawRectangle(250, 400, 400, 300, {200, 50, 50, 255});
    DrawRectangleLines(250, 400, 400, 300, RED);
    
    DrawText("GAME OVER!", 330, 430, 28, YELLOW);
    DrawText("No more moves!", 330, 490, 20, WHITE);
    DrawText("Press SPACE to try again", 310, 540, 16, WHITE);
}

void UI::showPause() {
    // Draw semi-transparent overlay
    DrawRectangle(0, 0, 900, 1200, {0, 0, 0, 150});
    
    // Draw popup
    DrawRectangle(300, 450, 300, 200, {100, 100, 200, 255});
    DrawRectangleLines(300, 450, 300, 200, WHITE);
    
    DrawText("PAUSED", 360, 480, 24, YELLOW);
    DrawText("Press P to resume", 330, 540, 16, WHITE);
}
=======
#include "game.h"
#include "config.h"
#include <sstream>

UI::UI(Game* g) : game(g) {
}

UI::~UI() = default;

void UI::update(float deltaTime) {
    // UI animations or updates
}

void UI::render() {
    drawScore();
    drawMoves();
    drawLevel();
    drawTimer();

    if (game->getState() == GameState::LEVEL_COMPLETE) {
        showLevelComplete();
    } else if (game->getState() == GameState::GAME_OVER) {
        showGameOver();
    } else if (game->getState() == GameState::PAUSED) {
        showPauseMenu();
    }
}

void UI::drawScore() {
    std::stringstream ss;
    ss << "Score: " << game->getScore();
    DrawTextA(ss.str().c_str(), 10, 10, 20, COLOR_WHITE);
}

void UI::drawMoves() {
    std::stringstream ss;
    ss << "Moves: " << game->getMovesLeft();
    DrawTextA(ss.str().c_str(), 10, 40, 20, COLOR_WHITE);
}

void UI::drawLevel() {
    std::stringstream ss;
    ss << "Level: " << game->getLevel();
    DrawTextA(ss.str().c_str(), 10, 70, 20, COLOR_WHITE);
}

void UI::drawTimer() {
    int minutes = static_cast<int>(game->getTimeLeft()) / 60;
    int seconds = static_cast<int>(game->getTimeLeft()) % 60;
    std::stringstream ss;
    ss << "Time: " << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
    DrawTextA(ss.str().c_str(), 10, 100, 20, COLOR_WHITE);
}

void UI::drawProgressBar(float progress, int x, int y, int width, int height) {
    DrawRectangleA(x, y, width, height, COLOR_GRAY);
    DrawRectangleA(x, y, static_cast<int>(width * progress), height, COLOR_GREEN);
}

void UI::drawTextCentered(const std::string& text, int y, int fontSize, ColorA color) {
    int textWidth = MeasureTextA(text.c_str(), fontSize);
    int screenWidth = GetScreenWidth();
    DrawTextA(text.c_str(), (screenWidth - textWidth) / 2, y, fontSize, color);
}

void UI::showLevelComplete() {
    drawTextCentered("LEVEL COMPLETE!", GetScreenHeight() / 2 - 50, 30, COLOR_GREEN);
    drawTextCentered("Tap to continue", GetScreenHeight() / 2, 20, COLOR_WHITE);
}

void UI::showGameOver() {
    drawTextCentered("GAME OVER", GetScreenHeight() / 2 - 50, 30, COLOR_RED);
    drawTextCentered("Tap to restart", GetScreenHeight() / 2, 20, COLOR_WHITE);
}

void UI::showPauseMenu() {
    drawTextCentered("PAUSED", GetScreenHeight() / 2 - 50, 30, COLOR_YELLOW);
    drawTextCentered("Tap to resume", GetScreenHeight() / 2, 20, COLOR_WHITE);
}
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
