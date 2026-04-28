#ifndef TILE_H
#define TILE_H

#include "config.h"
#include <cstdint>

enum class FruitType : uint8_t {
    Apple,
    Banana,
    Cherry,
    Grape,
    Lemon,
    Orange,
    Watermelon,
    Pineapple,
    None
};

enum class SpecialType : uint8_t {
    None,
    Striped,      // Horizontal or Vertical line
    Wrapped,      // Explosion effect
    Bomb,         // Large area effect
    ThreeInARow,  // Combo
};

class Tile {
public:
    Tile(int row, int col, FruitType type);
    ~Tile();
    
    void update(float dt);
    void render(float boardX, float boardY);
    
    // Getters
    FruitType getFruitType() const { return fruitType; }
    SpecialType getSpecialType() const { return specialType; }
    int getRow() const { return row; }
    int getCol() const { return col; }
    bool isAnimating() const { return isMoving || isMatching; }
    
    // Setters
    void setFruitType(FruitType type) { fruitType = type; }
    void setSpecialType(SpecialType type) { specialType = type; }
    void setPosition(int r, int c) { row = r; col = c; }
    
    // Animation
    void moveTo(int newRow, int newCol, float duration = 0.3f);
    void scaleOut(float duration = 0.2f);
    void highlight() { isHighlighted = true; }
    void unhighlight() { isHighlighted = false; }
    
    // Utility
    static Color getFruitColor(FruitType type);
    static char getFruitEmoji(FruitType type);
    
private:
    int row, col;
    float targetRow, targetCol;
    FruitType fruitType;
    SpecialType specialType;
    
    // Animation state
    float animationTime = 0.0f;
    float animationDuration = 0.0f;
    bool isMoving = false;
    bool isMatching = false;
    bool isHighlighted = false;
    float scale = 1.0f;
    float rotation = 0.0f;
    
    // Visual properties
    float bobOffset = 0.0f;
    float bobTime = 0.0f;
};

#endif // TILE_H
