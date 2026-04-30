#include "ui.h"
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