#include "board.h"
#include "particle_system.h"
#include "config.h"
#include <algorithm>
#include <random>

Board::Board(int w, int h, ParticleSystem* particleSys)
    : width(w), height(h), particleSystem(particleSys) {
    tiles.resize(height);
    for (auto& row : tiles) {
        row.resize(width);
        for (int x = 0; x < width; ++x) {
            FruitType type = static_cast<FruitType>(rand() % 8);
            row[x] = std::make_unique<Tile>(type, x, height - 1);
        }
    }
}

Board::~Board() = default;

void Board::update(float deltaTime) {
    for (auto& row : tiles) {
        for (auto& tile : row) {
            if (tile) tile->update(deltaTime);
        }
    }
}

void Board::render() {
    int tileSize = 50;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (tiles[y][x]) {
                tiles[y][x]->render();
            }
        }
    }
}

std::vector<std::vector<bool>> Board::findMatches() {
    std::vector<std::vector<bool>> matches(height, std::vector<bool>(width, false));

    // Horizontal matches
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width - 2; ++x) {
            if (tiles[y][x] && tiles[y][x+1] && tiles[y][x+2] &&
                tiles[y][x]->getType() == tiles[y][x+1]->getType() &&
                tiles[y][x]->getType() == tiles[y][x+2]->getType()) {
                matches[y][x] = matches[y][x+1] = matches[y][x+2] = true;
            }
        }
    }

    // Vertical matches
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height - 2; ++y) {
            if (tiles[y][x] && tiles[y+1][x] && tiles[y+2][x] &&
                tiles[y][x]->getType() == tiles[y+1][x]->getType() &&
                tiles[y][x]->getType() == tiles[y+2][x]->getType()) {
                matches[y][x] = matches[y+1][x] = matches[y+2][x] = true;
            }
        }
    }

    return matches;
}

void Board::removeMatches(const std::vector<std::vector<bool>>& matches) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (matches[y][x] && tiles[y][x]) {
                particleSystem->emitExplosion(x * 50, y * 50, tiles[y][x]->getFruitColor());
                tiles[y][x].reset();
            }
        }
    }
}

void Board::applyGravity() {
    for (int x = 0; x < width; ++x) {
        int writeY = height - 1;
        for (int y = height - 1; y >= 0; --y) {
            if (tiles[y][x]) {
                if (y != writeY) {
                    tiles[writeY][x] = std::move(tiles[y][x]);
                    tiles[writeY][x]->setPosition(x, writeY);
                }
                --writeY;
            }
        }
        // Fill empty spaces at top
        for (int y = 0; y <= writeY; ++y) {
            FruitType type = static_cast<FruitType>(rand() % 8);
            tiles[y][x] = std::make_unique<Tile>(type, x, y);
        }
    }
}

bool Board::processMatches() {
    auto matches = findMatches();
    bool hasMatches = false;
    for (const auto& row : matches) {
        for (bool match : row) {
            if (match) {
                hasMatches = true;
                break;
            }
        }
        if (hasMatches) break;
    }

    if (hasMatches) {
        removeMatches(matches);
        applyGravity();
    }

    return hasMatches;
}

bool Board::swapTiles(int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x1 >= width || y1 < 0 || y1 >= height ||
        x2 < 0 || x2 >= width || y2 < 0 || y2 >= height) {
        return false;
    }

    std::swap(tiles[y1][x1], tiles[y2][x2]);
    if (tiles[y1][x1]) tiles[y1][x1]->setPosition(x1, y1);
    if (tiles[y2][x2]) tiles[y2][x2]->setPosition(x2, y2);

    return true;
}

bool Board::isValidMove(int x, int y) {
    // Check if swapping with adjacent tiles creates matches
    // This is a simplified check
    return true; // For now
}