#include "tile.h"
#include "config.h"

Tile::Tile(FruitType t, int px, int py)
    : type(t), x(px), y(py), moveProgress(0.0f), moveDuration(0.0f), moving(false), selected(false) {
}

Tile::~Tile() = default;

void Tile::update(float deltaTime) {
    if (moving) {
        moveProgress += deltaTime / moveDuration;
        if (moveProgress >= 1.0f) {
            moving = false;
            moveProgress = 1.0f;
        }
    }
}

void Tile::render() {
    int tileSize = 50;
    int screenX = x * tileSize;
    int screenY = y * tileSize;

    ColorA color = getFruitColor();
    if (selected) {
        // Highlight selected tile
        DrawRectangleA(screenX - 2, screenY - 2, tileSize + 4, tileSize + 4, COLOR_WHITE);
    }

    DrawRectangleA(screenX, screenY, tileSize, tileSize, color);

    // Draw fruit emoji or simple shape
    const char* emoji = getFruitEmoji();
    int textWidth = MeasureTextA(emoji, 20);
    DrawTextA(emoji, screenX + (tileSize - textWidth) / 2, screenY + tileSize / 2 - 10, 20, COLOR_WHITE);
}

void Tile::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Tile::moveTo(int targetX, int targetY, float duration) {
    // For animation
    moveDuration = duration;
    moveProgress = 0.0f;
    moving = true;
}

ColorA Tile::getFruitColor() const {
    switch (type) {
        case FruitType::APPLE: return COLOR_RED;
        case FruitType::BANANA: return COLOR_YELLOW;
        case FruitType::ORANGE: return COLOR_ORANGE;
        case FruitType::GRAPE: return COLOR_PURPLE;
        case FruitType::STRAWBERRY: return COLOR_PINK;
        case FruitType::LEMON: return COLOR_YELLOW;
        case FruitType::CHERRY: return COLOR_RED;
        case FruitType::WATERMELON: return COLOR_GREEN;
        default: return COLOR_GRAY;
    }
}

const char* Tile::getFruitEmoji() const {
    switch (type) {
        case FruitType::APPLE: return "🍎";
        case FruitType::BANANA: return "🍌";
        case FruitType::ORANGE: return "🍊";
        case FruitType::GRAPE: return "🍇";
        case FruitType::STRAWBERRY: return "🍓";
        case FruitType::LEMON: return "🍋";
        case FruitType::CHERRY: return "🍒";
        case FruitType::WATERMELON: return "🍉";
        default: return "?";
    }
}