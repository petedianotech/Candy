#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include <vector>
#include <memory>
#include <functional>

class Board {
public:
    static const int WIDTH = 8;
    static const int HEIGHT = 8;
    static const int TILE_SIZE = 48;
    static const int BOARD_PADDING = 20;
    
    Board();
    ~Board();
    
    void init();
    void update(float dt);
    void render();
    
    // Interaction
    void selectTile(int row, int col);
    void swapTiles(int row1, int col1, int row2, int col2);
    bool isValidMove(int row, int col) const;
    
    // Matching and cascading
    void processMatches();
    bool hasMatches() const;
    void applyGravity();
    void fillEmpty();
    
    // Getters
    Tile* getTile(int row, int col) const;
    int getScore() const { return score; }
    int getMoves() const { return moves; }
    void resetScore() { score = 0; }
    void addScore(int points) { score += points; }
    void decrementMoves() { if (moves > 0) moves--; }
    
    // Callbacks
    using OnScoreCallback = std::function<void(int)>;
    void setOnScoreCallback(OnScoreCallback cb) { onScoreCallback = cb; }
    
private:
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    std::vector<std::vector<bool>> toBeRemoved;
    
    int score;
    int moves;
    float swapAnimationTime;
    float cascadeDelay;
    
    int selectedRow = -1;
    int selectedCol = -1;
    
    OnScoreCallback onScoreCallback;
    
    // Utility methods
    void createRandomTile(int row, int col);
    bool findMatches();
    bool checkMatch(int row, int col);
    std::vector<std::pair<int, int>> getMatchGroup(int row, int col);
    void markForRemoval(int row, int col);
    bool canSwap(int row1, int col1, int row2, int col2);
    bool createsMatch(int row1, int col1, int row2, int col2);
    void renderTiles();
    void renderSelection();
};

#endif // BOARD_H
