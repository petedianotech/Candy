#include "tile.h"
<<<<<<< HEAD
#include <cmath>

Tile::Tile(int row, int col, FruitType type)
    : row(row), col(col), targetRow(row), targetCol(col), 
      fruitType(type), specialType(SpecialType::None),
      bobTime(0) {
}

Tile::~Tile() {
}

void Tile::update(float dt) {
    // Handle falling animation
    if (isMoving) {
        animationTime += dt;
        if (animationTime >= animationDuration) {
            animationTime = animationDuration;
            isMoving = false;
            row = (int)targetRow;
            col = (int)targetCol;
        }
    }
    
    // Handle matching animation (scale out)
    if (isMatching) {
        animationTime += dt;
        if (animationTime >= animationDuration) {
            animationTime = animationDuration;
            isMatching = false;
            scale = 0.0f;
        } else {
            scale = 1.0f - (animationTime / animationDuration);
        }
    }
    
    // Bobbing animation for idle tiles
    bobTime += dt;
    bobOffset = std::sin(bobTime * 4.0f) * 2.0f;
    
    // Rotation for special tiles
    if (specialType != SpecialType::None) {
        rotation += dt * 2.0f;
        if (rotation > 6.28f) rotation -= 6.28f;
    }
}

void Tile::render(float boardX, float boardY) {
    if (fruitType == FruitType::None) return;
    
    const int TILE_SIZE = 48;
    const int PADDING = 20;
    
    float x = boardX + PADDING + col * TILE_SIZE + TILE_SIZE / 2;
    float y = boardY + PADDING + row * TILE_SIZE + TILE_SIZE / 2 + bobOffset;
    
    // Handle animation
    if (isMoving) {
        const float progress = animationTime / animationDuration;
        y = boardY + PADDING + (row + progress * (targetRow - row)) * TILE_SIZE + TILE_SIZE / 2 + bobOffset;
    }
    
    Color tileColor = getFruitColor(fruitType);
    
    if (isHighlighted) {
        tileColor = { (uint8_t)(tileColor.r * 1.3), (uint8_t)(tileColor.g * 1.3), 
                      (uint8_t)(tileColor.b * 1.3), 255 };
    }
    
    // Draw main tile with scaling
    DrawCircle((int)x, (int)y, (TILE_SIZE / 2 - 2) * scale, tileColor);
    
    // Draw outline
    DrawCircleLines((int)x, (int)y, TILE_SIZE / 2 - 2, DARKGRAY);
    
    // Draw special indicator
    if (specialType == SpecialType::Striped) {
        DrawLineEx({x - 8, y}, {x + 8, y}, 2, WHITE);
        DrawLineEx({x - 6, y - 6}, {x + 6, y + 6}, 1, WHITE);
        DrawLineEx({x - 6, y + 6}, {x + 6, y - 6}, 1, WHITE);
    } else if (specialType == SpecialType::Wrapped) {
        DrawRing({x, y}, TILE_SIZE / 2 - 6, TILE_SIZE / 2 - 4, 0, 360, 8, WHITE);
    } else if (specialType == SpecialType::Bomb) {
        DrawCircleLines((int)x, (int)y, TILE_SIZE / 2 - 8, GOLD);
    }
    
    // Add shine effect
    DrawCircle((int)(x - TILE_SIZE / 6), (int)(y - TILE_SIZE / 6), 4, WHITE);
}

void Tile::moveTo(int newRow, int newCol, float duration) {
    targetRow = newRow;
    targetCol = newCol;
    animationDuration = duration;
    animationTime = 0.0f;
    isMoving = true;
}

void Tile::scaleOut(float duration) {
    animationDuration = duration;
    animationTime = 0.0f;
    isMatching = true;
}

Color Tile::getFruitColor(FruitType type) {
    switch (type) {
        case FruitType::Apple:      return { 255, 0, 0, 255 };      // Red
        case FruitType::Banana:     return { 255, 255, 0, 255 };    // Yellow
        case FruitType::Cherry:     return { 220, 20, 60, 255 };    // Crimson
        case FruitType::Grape:      return { 128, 0, 128, 255 };    // Purple
        case FruitType::Lemon:      return { 255, 250, 0, 255 };    // Lemon
        case FruitType::Orange:     return { 255, 165, 0, 255 };    // Orange
        case FruitType::Watermelon: return { 34, 139, 34, 255 };    // Dark Green
        case FruitType::Pineapple:  return { 255, 215, 0, 255 };    // Goldenrod
        default:                    return LIGHTGRAY;
    }
}

char Tile::getFruitEmoji(FruitType type) {
    switch (type) {
        case FruitType::Apple:      return 'A';
        case FruitType::Banana:     return 'B';
        case FruitType::Cherry:     return 'C';
        case FruitType::Grape:      return 'G';
        case FruitType::Lemon:      return 'L';
        case FruitType::Orange:     return 'O';
        case FruitType::Watermelon: return 'W';
        case FruitType::Pineapple:  return 'P';
        default:                    return '?';
    }
}
=======
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
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
