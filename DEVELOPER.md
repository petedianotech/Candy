# Fruit Burst - Developer Guide

Welcome to the Fruit Burst development guide! This document helps developers understand the codebase and extend the game with new features.

## Quick Start for Developers

### 1. Get the Code
```bash
cd /workspaces/Candy
git clone <repo-url>
cd Candy
```

### 2. Build the Project
```bash
mkdir build && cd build
cmake ..
cmake --build . -j4
./FruitBurst
```

### 3. Explore the Structure
- `include/` - All header files (one per component)
- `src/` - Implementation files
- `CMakeLists.txt` - Build configuration
- `README.md` - Game documentation
- `ARCHITECTURE.md` - Code architecture
- `FEATURES.md` - Feature list
- `BUILDING.md` - Build guide (this file)

## Code Style Guide

### Naming Conventions

**Classes**: PascalCase
```cpp
class InputHandler { };
class ParticleSystem { };
```

**Functions/Methods**: camelCase
```cpp
void updateGame(float dt);
bool isValidMove(int row, int col);
```

**Variables**: camelCase
```cpp
int selectedRow;
float animationTime;
bool isMoving;
```

**Constants**: UPPER_CASE or camelCase (class constants)
```cpp
const int TILE_SIZE = 48;
const int Board::WIDTH = 8;
```

**Enums**: PascalCase for enum, UPPER_CASE for values
```cpp
enum class GameState {
    Playing,
    Paused,
    LevelComplete
};
```

### Code Formatting

**Indentation**: 4 spaces (no tabs)
```cpp
if (condition) {
    statement;
}
```

**Line Length**: Maximum 100 characters (hard limit 120)
```cpp
// Good
result = complexFunction(param1, param2, param3);

// Bad - too long
very_long_variable_name = extremely_long_function_name_with_many_parameters(param1, param2, param3);
```

**Braces**: Allman style for functions, K&R for control flow
```cpp
// Functions
void MyClass::myMethod()
{
    // implementation
}

// Control flow
if (condition) {
    statement;
} else {
    other();
}
```

### Documentation Style

**Class Documentation**:
```cpp
/// Manages the game board state and match detection
class Board {
public:
    /// Initialize the board with random tiles
    void init();
};
```

**Function Documentation**:
```cpp
/// Detects if tiles match at given position
/// @param row The row index (0-7)
/// @param col The column index (0-7)
/// @return True if part of a match group
/// @see findMatches()
bool Board::checkMatch(int row, int col);
```

**Inline Comments**:
```cpp
// Only use for non-obvious logic
if (cascadeDelay <= 0) {  // Only process cascades when animation completes
    processMatches();
}
```

## Architecture Understanding

### Key Principles

1. **Single Responsibility**: Each class has one job
   - `Tile`: Represents a single fruit
   - `Board`: Manages grid and logic
   - `UI`: Renders interface
   - `Game`: Orchestrates everything

2. **Dependency Injection**: Components don't create their dependencies
   ```cpp
   // Good: dependencies passed in
   class Game {
       Game(std::unique_ptr<Board> board, ...) { }
   };
   
   // Bad: creates own dependencies
   class Game {
       Board board;  // Tightly coupled
   };
   ```

3. **Composition Over Inheritance**: Use composition
   ```cpp
   class Game {
       std::unique_ptr<Board> board;  // Composition
       std::unique_ptr<UI> ui;
   };
   ```

4. **Memory Safety**: Use smart pointers
   ```cpp
   std::unique_ptr<Board> board;    // Automatic cleanup
   std::make_unique<Board>();
   ```

## Common Development Tasks

### Task 1: Add a New Fruit Type

**Step 1**: Update enum in `include/tile.h`
```cpp
enum class FruitType : uint8_t {
    // ... existing fruits ...
    Kiwi,        // New fruit
};
```

**Step 2**: Add color in `src/tile.cpp`
```cpp
Color Tile::getFruitColor(FruitType type) {
    switch (type) {
        // ...
        case FruitType::Kiwi: return { 50, 180, 50, 255 };  // Green
    }
}
```

**Step 3**: Update board generation in `src/board.cpp`
```cpp
void Board::createRandomTile(int row, int col) {
    FruitType types[] = {
        FruitType::Apple, FruitType::Banana, FruitType::Cherry,
        // ... all fruit types including new Kiwi
        FruitType::Kiwi
    };
    // Rest of function unchanged
}
```

**Step 4**: Build and test
```bash
cd build && cmake --build . && ./FruitBurst
```

### Task 2: Modify Scoring Rules

**File**: `src/board.cpp`

**Current Code**:
```cpp
void Board::processMatches() {
    if (!findMatches()) return;
    
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            if (toBeRemoved[row][col] && tiles[row][col]) {
                score += 10;  // 10 points per tile
            }
        }
    }
}
```

**Modification Example** - 4-in-a-row bonus:
```cpp
void Board::processMatches() {
    if (!findMatches()) return;
    
    int matchCount = 0;
    for (int row = 0; row < HEIGHT; ++row) {
        for (int col = 0; col < WIDTH; ++col) {
            if (toBeRemoved[row][col] && tiles[row][col]) {
                matchCount++;
                score += 10;
            }
        }
    }
    
    // 4-in-a-row bonus
    if (matchCount >= 4) {
        score += 50;  // Extra bonus
    }
}
```

### Task 3: Add a New Game State

**Step 1**: Add state to enum in `include/game.h`
```cpp
enum class GameState {
    Playing,
    Paused,
    LevelComplete,
    GameOver,
    Tutorial  // New state
};
```

**Step 2**: Implement handling in `src/game.cpp`
```cpp
void Game::update(float dt) {
    switch (state) {
        // ... existing cases ...
        case GameState::Tutorial:
            if (IsKeyPressed(KEY_SPACE)) {
                state = GameState::Playing;
            }
            break;
    }
}

void Game::render() {
    // ... existing code ...
    switch (state) {
        case GameState::Tutorial:
            ui->showTutorial();  // Implement in UI
            break;
    }
}
```

###  Task 4: Increase Difficulty

**File**: `src/game.cpp`

**Current**:
```cpp
void Game::nextLevel() {
    currentLevel++;
    targetScore += 200;      // 500 → 700 → 900 ...
    moves = 20 + (currentLevel - 1) * 5;  // 20 → 25 → 30 ...
}
```

**Harder**:
```cpp
void Game::nextLevel() {
    currentLevel++;
    targetScore += 300;      // Even harder target
    moves = 20 + (currentLevel - 1) * 3;  // Fewer moves
    levelTime = 300 - (currentLevel * 10);  // Tighter time
}
```

## Debugging Tips

### Enable Debug Information
```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

### GDB Debugging
```bash
gdb ./FruitBurst
(gdb) run
(gdb) bt  # Backtrace on crash
(gdb) break board.cpp:100
(gdb) continue
```

### LLDB Debugging (macOS)
```bash
lldb ./FruitBurst
(lldb) b board.cpp:100
(lldb) run
```

### Print Debugging
```cpp
#include <iostream>

// In game loop
std::cout << "Score: " << score << " Moves: " << moves << std::endl;
std::cout << "Match at (" << row << "," << col << ")" << std::endl;
```

## Testing Strategy

### Unit Test Example (Pseudo-code)
```cpp
// In test file
void testMatchDetection() {
    Board board;
    board.init();
    
    // Create specific match scenario
    // ...
    
    assert(board.hasMatches() == true);
    std::cout << "✓ Match detection works" << std::endl;
}
```

### Manual Testing Checklist
- [ ] Game launches without crashes
- [ ] Tiles swap correctly
- [ ] Matches are detected
- [ ] Particles display
- [ ] Score updates
- [ ] Moves decrement
- [ ] Level progresses
- [ ] Game over conditions trigger
- [ ] UI displays correctly
- [ ] All 8 fruit types appear

## Performance Profiling

### Frame Time Analysis
```cpp
float frameTime = GetFrameTime();
if (frameTime > 0.020f) {  // More than 20ms
    std::cout << "Frame took " << frameTime * 1000 << "ms" << std::endl;
}
```

### Memory Profiling
```bash
valgrind --leak-check=full ./FruitBurst
```

### Compile Time Analysis
```bash
time cmake --build . -j1
```

## Common Patterns

### Observer Pattern (Callbacks)
```cpp
// Definition in header
using OnScoreCallback = std::function<void(int)>;
void setOnScoreCallback(OnScoreCallback cb) { onScoreCallback = cb; }

// Usage
board->setOnScoreCallback([this](int score) {
    uiScore = score;
    soundManager->playMatchSound();
});

// Invocation
if (onScoreCallback) onScoreCallback(points);
```

### State Machine
```cpp
enum class State { Idle, Moving, Matched };

void update(float dt) {
    switch (state) {
        case State::Idle:
            // Handle idle
            break;
        case State::Moving:
            // Handle movement
            break;
        case State::Matched:
            // Handle removal
            break;
    }
}
```

### RAII (Resource Acquisition Is Initialization)
```cpp
// Automatic cleanup when out of scope
{
    std::unique_ptr<Board> board = std::make_unique<Board>();
    // ... use board ...
} // Automatically deleted here, destructor called
```

## Extending for Different Platforms

### Web (Emscripten)
```bash
emcmake cmake ..
emmake make
```

### Mobile (React Native/Flutter)
Create C++ bindings and integrate as native module.

### Console Support
Extend InputHandler for gamepad input.

## Performance Optimization Tips

### 1. Reduce Allocations
```cpp
// Bad: Allocates every frame
std::vector<int> matches;
matches.push_back(i);  // Allocation

// Good: Reuse container
class Board {
    std::vector<int> matches;  // Allocated once
    void findMatches() {
        matches.clear();
        matches.push_back(i);  // No allocation
    }
};
```

### 2. Use References
```cpp
// Bad: Copies
void render(Tile tile) { }

// Good: Reference
void render(const Tile& tile) { }
```

### 3. Cache Calculations
```cpp
// Bad: Recalculate every frame
float opacity = lifeTime / maxLifeTime;
opacity = opacity * 255;

// Good: Calculate once
float cachedOpacity = lifeTime / maxLifeTime;
```

## Continuous Integration

### GitHub Actions Example
```yaml
name: Build & Test
on: [push, pull_request]
jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - run: mkdir build && cd build && cmake .. && cmake --build .
```

## Code Review Checklist

When reviewing changes:
- [ ] Follows naming conventions
- [ ] Proper error handling
- [ ] Memory safe (smart pointers)
- [ ] No resource leaks
- [ ] Performance acceptable
- [ ] Documented
- [ ] Tests added
- [ ] No breaking changes to API

## Git Workflow

```bash
# Create feature branch
git checkout -b feature/new-fruit-type

# Make changes
# ...

# Commit
git commit -m "feat: add Kiwi fruit type"

# Push
git push origin feature/new-fruit-type

# Create pull request on GitHub
```

## Commit Message Format

```
type(scope): subject

body

footer
```

**Types**: feat, fix, docs, style, refactor, test, chore

**Example**:
```
feat(board): add 4-in-a-row scoring bonus

Add 50 point bonus when 4 or more tiles match.
Detects match count and applies bonus after removal.

Closes #42
```

## Resources

- [Modern C++ Best Practices](https://isocpp.org/guidelines/cppcoreguidelines)
- [Raylib Documentation](https://www.raylib.com/docs/)
- [Game Programming Patterns](https://gameprogrammingpatterns.com/)
- [CMake Documentation](https://cmake.org/documentation/)

## Getting Help

1. Check existing documentation
2. Search code comments for similar features
3. Look at existing implementations
4. Ask in discussion forums or issues

## Future Development Paths

### System Design: Power-up Mechanics
Implement special tile creation when matches occur:
```cpp
// On 4-in-a-row match
if (matchCount == 4) {
    createSpecialTile(row, col, SpecialType::Striped);
}
```

### System Design: Multiplayer
Async turn-based with network:
```cpp
class NetworkGame : public Game {
    void submitMove(...);
    void receiveOpponentMove(...);
};
```

### System Design: Leaderboard
```cpp
class Leaderboard {
    void uploadScore(int score, int time);
    std::vector<Score> getTopScores();
};
```

---

Happy coding! If you have questions, check the inline code comments or refer to ARCHITECTURE.md for more details.
