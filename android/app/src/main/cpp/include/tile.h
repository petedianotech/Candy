#pragma once

#include "config.h"

enum class FruitType {
    APPLE,
    BANANA,
    ORANGE,
    GRAPE,
    STRAWBERRY,
    LEMON,
    CHERRY,
    WATERMELON
};

class Tile {
public:
    Tile(FruitType type, int x, int y);
    ~Tile();

    void update(float deltaTime);
    void render();

    FruitType getType() const { return type; }
    int getX() const { return x; }
    int getY() const { return y; }

    void setPosition(int newX, int newY);
    void moveTo(int targetX, int targetY, float duration);

    bool isMoving() const { return moving; }
    bool isSelected() const { return selected; }
    void setSelected(bool sel) { selected = sel; }

private:
    FruitType type;
    int x, y;
    float moveProgress;
    float moveDuration;
    bool moving;
    bool selected;

public:
    ColorA getFruitColor() const;
    const char* getFruitEmoji() const;
};