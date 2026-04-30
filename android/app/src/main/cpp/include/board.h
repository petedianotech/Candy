#pragma once

#include <vector>
#include <memory>
#include "tile.h"
#include "config.h"

class ParticleSystem;

class Board {
public:
    Board(int width, int height, ParticleSystem* particleSys);
    ~Board();

    void update(float deltaTime);
    void render();

    bool processMatches();
    void applyGravity();
    bool swapTiles(int x1, int y1, int x2, int y2);
    bool isValidMove(int x, int y);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    const std::vector<std::vector<std::unique_ptr<Tile>>>& getTiles() const { return tiles; }

private:
    int width, height;
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    ParticleSystem* particleSystem;

    std::vector<std::vector<bool>> findMatches();
    void removeMatches(const std::vector<std::vector<bool>>& matches);
    void fillEmptySpaces();
    bool hasValidMoves();
};