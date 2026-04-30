#include "board.h"
<<<<<<< HEAD
#include <cstdlib>
#include <ctime>
#include <algorithm>

Board::Board() 
    : score(0), moves(20), swapAnimationTime(0), cascadeDelay(0) {
    tiles.resize(HEIGHT);
    toBeRemoved.resize(HEIGHT);
    for (int i = 0; i < HEIGHT; ++i) {
        tiles[i].resize(WIDTH);
        toBeRemoved[i].resize(WIDTH, false);
    }
    srand((unsigned int)time(nullptr));
}

Board::~Board() {
}

void Board::init() {
    // Create initial board
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            createRandomTile(row, col);
        }
    }
    
    // Remove any initial matches
    findMatches();
    while (hasMatches()) {
        for (int row = 0; row < HEIGHT; ++row) {
            for (int col = 0; col < WIDTH; ++col) {
                if (toBeRemoved[row][col]) {
                    createRandomTile(row, col);
                    toBeRemoved[row][col] = false;
                }
            }
        }
        findMatches();
    }
}

void Board::update(float dt) {
    cascadeDelay -= dt;
    
    // Update all tiles
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            if (tiles[row][col]) {
                tiles[row][col]->update(dt);
            }
        }
    }
    
    // Check for cascade completion
    if (cascadeDelay <= 0) {
        bool isAnimating = false;
        for (int row = 0; row < HEIGHT; ++row) {
            for (int col = 0; col < WIDTH; ++col) {
                if (tiles[row][col] && tiles[row][col]->isAnimating()) {
                    isAnimating = true;
                    break;
                }
            }
            if (isAnimating) break;
        }
        
        if (!isAnimating) {
            processMatches();
=======
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
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
        }
    }
}

void Board::render() {
<<<<<<< HEAD
    renderTiles();
    renderSelection();
}

void Board::selectTile(int row, int col) {
    if (!isValidMove(row, col)) return;
    
    if (selectedRow == -1) {
        // First selection
        selectedRow = row;
        selectedCol = col;
        if (tiles[row][col]) {
            tiles[row][col]->highlight();
        }
    } else if (selectedRow == row && selectedCol == col) {
        // Deselect
        if (tiles[row][col]) {
            tiles[row][col]->unhighlight();
        }
        selectedRow = -1;
        selectedCol = -1;
    } else if (std::abs(selectedRow - row) + std::abs(selectedCol - col) == 1) {
        // Adjacent tile - attempt swap
        if (tiles[selectedRow][selectedCol]) {
            tiles[selectedRow][selectedCol]->unhighlight();
        }
        swapTiles(selectedRow, selectedCol, row, col);
        selectedRow = -1;
        selectedCol = -1;
    }
}

void Board::swapTiles(int row1, int col1, int row2, int col2) {
    if (!canSwap(row1, col1, row2, col2)) {
        return;
    }
    
    // Swap
    std::swap(tiles[row1][col1], tiles[row2][col2]);
    
    // Update positions
    if (tiles[row1][col1]) {
        tiles[row1][col1]->setPosition(row1, col1);
        tiles[row1][col1]->moveTo(row1, col1, 0.2f);
    }
    if (tiles[row2][col2]) {
        tiles[row2][col2]->setPosition(row2, col2);
        tiles[row2][col2]->moveTo(row2, col2, 0.2f);
    }
    
    decrementMoves();
    
    // Check for matches with delay
    cascadeDelay = 0.3f;
}

bool Board::isValidMove(int row, int col) const {
    return row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH;
}

void Board::processMatches() {
    if (!findMatches()) {
        return;
    }
    
    // Mark matched tiles to be removed
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            if (toBeRemoved[row][col] && tiles[row][col]) {
                tiles[row][col]->scaleOut(0.2f);
                score += 10;
                if (onScoreCallback) {
                    onScoreCallback(score);
                }
            }
        }
    }
    
    cascadeDelay = 0.3f;
}

bool Board::hasMatches() const {
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            if (toBeRemoved[row][col]) {
                return true;
            }
        }
    }
    return false;
}

bool Board::findMatches() {
    // Clear previous marks
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            toBeRemoved[row][col] = false;
        }
    }
    
    bool foundMatch = false;
    
    // Check horizontal matches
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH - 2; ++col) {
            if (tiles[row][col] && tiles[row][col + 1] && tiles[row][col + 2]) {
                if (tiles[row][col]->getFruitType() == tiles[row][col + 1]->getFruitType() &&
                    tiles[row][col]->getFruitType() == tiles[row][col + 2]->getFruitType() &&
                    tiles[row][col]->getFruitType() != FruitType::None) {
                    toBeRemoved[row][col] = true;
                    toBeRemoved[row][col + 1] = true;
                    toBeRemoved[row][col + 2] = true;
                    foundMatch = true;
                }
            }
        }
    }
    
    // Check vertical matches
    for (int col = 0; col < WIDTH; ++col) {
        for (int row = 0; row < HEIGHT - 2; ++row) {
            if (tiles[row][col] && tiles[row + 1][col] && tiles[row + 2][col]) {
                if (tiles[row][col]->getFruitType() == tiles[row + 1][col]->getFruitType() &&
                    tiles[row][col]->getFruitType() == tiles[row + 2][col]->getFruitType() &&
                    tiles[row][col]->getFruitType() != FruitType::None) {
                    toBeRemoved[row][col] = true;
                    toBeRemoved[row + 1][col] = true;
                    toBeRemoved[row + 2][col] = true;
                    foundMatch = true;
                }
            }
        }
    }
    
    return foundMatch;
}

void Board::applyGravity() {
    for (int col = 0; col < WIDTH; ++col) {
        for (int row = HEIGHT - 1; row >= 0; --row) {
            if (tiles[row][col] == nullptr || tiles[row][col]->getFruitType() == FruitType::None) {
                // Found empty space, look up for tile to fall
                for (int searchRow = row - 1; searchRow >= 0; --searchRow) {
                    if (tiles[searchRow][col] && tiles[searchRow][col]->getFruitType() != FruitType::None) {
                        // Move tile down
                        tiles[row][col] = std::move(tiles[searchRow][col]);
                        tiles[row][col]->setPosition(row, col);
                        tiles[row][col]->moveTo(row, col, 0.3f);
                        tiles[searchRow][col] = nullptr;
                        break;
                    }
                }
            }
        }
    }
}

void Board::fillEmpty() {
    for (int col = 0; col < WIDTH; ++col) {
        for (int row = 0; row < HEIGHT; ++row) {
            if (tiles[row][col] == nullptr || tiles[row][col]->getFruitType() == FruitType::None) {
                createRandomTile(row, col);
                tiles[row][col]->moveTo(row, col, 0.5f);
            }
        }
    }
}

Tile* Board::getTile(int row, int col) const {
    if (!isValidMove(row, col)) return nullptr;
    return tiles[row][col].get();
}

void Board::createRandomTile(int row, int col) {
    FruitType types[] = {
        FruitType::Apple, FruitType::Banana, FruitType::Cherry,
        FruitType::Grape, FruitType::Lemon, FruitType::Orange,
        FruitType::Watermelon, FruitType::Pineapple
    };
    
    FruitType type = types[rand() % 8];
    tiles[row][col] = std::make_unique<Tile>(row, col, type);
}

bool Board::canSwap(int row1, int col1, int row2, int col2) {
    if (!isValidMove(row1, col1) || !isValidMove(row2, col2)) return false;
    if (tiles[row1][col1] == nullptr || tiles[row2][col2] == nullptr) return false;
    return moves > 0;
}

void Board::renderTiles() {
    const float boardX = 50;
    const float boardY = 150;
    
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            if (tiles[row][col]) {
                tiles[row][col]->render(boardX, boardY);
            }
        }
    }
}

void Board::renderSelection() {
    if (selectedRow == -1) return;
    
    const float boardX = 50;
    const float boardY = 150;
    const int TILE_SIZE = 48;
    const int PADDING = 20;
    
    float x = boardX + PADDING + selectedCol * TILE_SIZE + TILE_SIZE / 2;
    float y = boardY + PADDING + selectedRow * TILE_SIZE + TILE_SIZE / 2;
    
    DrawCircleLines((int)x, (int)y, TILE_SIZE / 2 + 2, YELLOW);
}
=======
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
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
