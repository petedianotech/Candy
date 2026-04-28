# Fruit Burst - Architecture & Code Structure

## Project Overview

Fruit Burst is a professional-grade match-3 puzzle game built with modern C++17. It demonstrates best practices in game architecture, SOLID principles, and production-ready code quality.

## Directory Structure

```
/workspaces/Candy/
├── include/                    # Header files
│   ├── config.h               # Configuration and platform abstraction
│   ├── game.h                 # Main game controller
│   ├── board.h                # Game board logic
│   ├── tile.h                 # Individual tile/fruit representation
│   ├── input_handler.h        # Input management system
│   ├── ui.h                   # User interface rendering
│   ├── particle_system.h      # Visual effects
│   └── sound_manager.h        # Audio management
├── src/                        # Implementation files
│   ├── main.cpp               # Entry point
│   ├── game.cpp               # Game loop and state machine
│   ├── board.cpp              # Board management and match logic
│   ├── tile.cpp               # Tile animation and rendering
│   ├── input_handler.cpp      # Input processing
│   ├── ui.cpp                 # UI drawing
│   ├── particle_system.cpp    # Particle effects
│   └── sound_manager.cpp      # Audio playing
├── CMakeLists.txt             # Build configuration
├── README.md                  # User documentation
├── BUILDING.md                # Build instructions
└── ARCHITECTURE.md            # This file
```

## Architecture Patterns

### 1. Model-View-Controller (MVC)
```
Model Layer:
  └── Board (game state)
      └── Tile array
      └── Match detection logic

View Layer:
  ├── UI (scores, UI elements)
  ├── Tile rendering
  └── ParticleSystem (visual effects)

Controller Layer:
  └── Game (main controller)
      ├── Manages game state
      └── Coordinates components
```

### 2. Component Architecture
```
Game
├── Board (game logic)
├── InputHandler (user input)
├── UI (graphics rendering)
├── ParticleSystem (effects)
└── SoundManager (audio)
```

### 3. State Machine
```
Game States:
┌─────────────┐
│   Playing   │ ---> LevelComplete ---> NextLevel
└─────────────┤
    ↑         |
    |         └────> GameOver
    └─────P key────> Paused
```

## Core Components

### config.h - Platform Abstraction
**Purpose**: Provides compatibility layer for multiple graphics backends

**Features**:
- Conditional compilation for Raylib/SDL2/Headless
- Stub implementations for headless builds
- Type definitions and constants
- Graphics function wrappers

**Usage**:
```cpp
#include "config.h"

// Works with Raylib, SDL2, or headless mode
DrawCircle(x, y, radius, color);
```

### game.h/game.cpp - Main Game Controller
**Purpose**: Main game loop and state management

**Key Responsibilities**:
- Game loop execution
- State transitions
- Component coordination
- Update/Render cycle

**Design Pattern**: State Machine

**Class Hierarchy**:
```
class Game {
  enum GameState { Playing, Paused, LevelComplete, GameOver }
  std::unique_ptr<Board> board
  std::unique_ptr<InputHandler> inputHandler
  std::unique_ptr<UI> ui
  std::unique_ptr<ParticleSystem> particleSystem
  std::unique_ptr<SoundManager> soundManager
}
```

### board.h/board.cpp - Game Board Logic
**Purpose**: Manages game state, match detection, and physics

**Key Features**:
- 8x8 tile grid
- Match-3 detection algorithm
- Gravity simulation
- Tile cascading
- Score calculation

**Match Detection Algorithm**:
```
For each tile:
  Check horizontal: 3+ consecutive same-type tiles
  Check vertical: 3+ consecutive same-type tiles
  Mark matched tiles for removal
```

**Tile Physics**:
```
1. Apply Gravity: Tiles fall downward
2. Cascade: After removal, tiles settle
3. Fill: Generate new tiles at top
4. Match Again: Detect cascades
```

**Complexity**: O(n²) for match detection, O(n) for gravity

### tile.h/tile.cpp - Tile/Fruit Representation
**Purpose**: Individual fruit tile with animation

**Features**:
- 8 fruit types (Apple, Banana, Cherry, etc.)
- 4 special types (Striped, Wrapped, Bomb, ThreeInARow)
- Smooth animations
- Bobbing idle effect
- Shine effects

**Fruit Types**:
```
enum FruitType {
  Apple (Red),
  Banana (Yellow),
  Cherry (Crimson),
  Grape (Purple),
  Lemon (Yellow),
  Orange (Orange),
  Watermelon (Green),
  Pineapple (Goldenrod)
}
```

**Animation System**:
```
State Machine for each Tile:
  Idle (bobbing)
    ↓
  Moving (linear interpolation)
    ↓
  Matched (scale out with particles)
```

### input_handler.h/input_handler.cpp - Input System
**Purpose**: Abstracts input handling with callback pattern

**Input Sources**:
- Mouse clicks (tile selection/swapping)
- Keyboard (P=pause, ESC=exit, SPACE=continue)

**Design Pattern: Observer (Callbacks)**
```cpp
inputHandler->setMouseClickCallback([](float x, float y) {
  // Handle click
});

inputHandler->setKeyPressCallback([](int key) {
  // Handle key
});
```

### ui.h/ui.cpp - User Interface
**Purpose**: Renders all UI elements

**Elements**:
- Score display
- Move counter
- Level indicator
- Progress bar (current/target score)
- Timer
- Level complete popup
- Game over screen
- Pause overlay

**Layout**:
```
┌─────────────────────────────────────────┐
│  Fruit Burst    SCORE: 1250             │
│  Level: 3       Moves: 12/20   Time: 4:32│
│  Progress: ████████░░░░░░░░             │
├─────────────────────────────────────────┤
│                                         │
│          [Game Board 8x8]              │
│                                         │
└─────────────────────────────────────────┘
```

### particle_system.h/particle_system.cpp - Visual Effects
**Purpose**: Manages particle effects for visual polish

**Particle Types**:
- **Explosion**: Radial burst when tiles match
- **Match**: Color-specific particles
- **PowerUp**: Multi-directional burst
- **Combo**: Special effect for cascades

**Physics**:
- Velocity-based movement
- Gravity simulation
- Alpha fade-out
- Size scaling

### sound_manager.h/sound_manager.cpp - Audio System
**Purpose**: Manages game audio (framework ready)

**Sound Events**:
- Match sound
- Swap sound
- Power-up activation
- Combo achieved
- Level complete
- Button click

**Framework**: Prepared for audio integration with Raylib audio

## Data Structures

### Game Board
```cpp
// 8x8 grid of unique_ptr<Tile>
std::vector<std::vector<std::unique_ptr<Tile>>> tiles[8][8];

// Marks which tiles should be removed
std::vector<std::vector<bool>> toBeRemoved[8][8];
```

### Particle Pool
```cpp
// Dynamic particle storage
std::vector<std::unique_ptr<Particle>> particles;

// Particles are cleaned up when lifeTime <= 0
```

## Algorithm Analysis

### Match Detection
```
Time Complexity: O(WIDTH * HEIGHT) = O(64) = O(1)
Space Complexity: O(WIDTH * HEIGHT) = O(64) = O(1)
```

### Gravity Simulation
```
Time Complexity: O(WIDTH * HEIGHT²) - worst case all tiles fall
Space Complexity: O(1)
```

### Cascading System
```
Worst Case: Every tile in column causes cascade
Time Complexity: O(HEIGHT * number_of_cascades)
```

## Memory Management

### RAII Pattern
All dynamic resources use smart pointers:
```cpp
std::unique_ptr<Board> board;       // Auto-deleted in destructor
std::unique_ptr<Particle> particle; // Auto-freed when done
```

### Performance Considerations
- Pre-allocated grid (no dynamic allocation during gameplay)
- Particle pool (create/destroy as needed)
- String optimization (minimal string usage in game loop)

## Game Loop

```cpp
while (!WindowShouldClose() && game.isRunning()) {
  float dt = GetFrameTime();  // Frame time
  
  // Update Phase
  game.update(dt);
    ├── Handle input
    ├── Process game logic
    ├── Detect matches
    ├── Apply gravity
    ├── Update animations
    └── Update UI state
  
  // Render Phase
  BeginDrawing();
    game.render();
      ├── Render board
      ├── Render particles
      ├── Render UI overlay
      └── Render state popups
  EndDrawing();
}
```

### Frame Time Independence
All movement/animation uses `dt` for frame-rate independence:
```cpp
position += velocity * dt;  // Frame-rate independent
```

## Threading Considerations

Currently single-threaded. Future enhancements could include:
- Async level loading
- Background music streaming
- Particle effect rendering on GPU

## Error Handling

### Current Strategy
- Exception-based for initialization errors
- Return values for game logic errors
- Silent failure for missing assets (graceful degradation)

### Future Improvements
- Event logging system
- User-facing error messages
- Crash recovery/auto-save

## Extensions & Hooks

### Adding New Features

**New Fruit Type**:
```cpp
// 1. Add to enum in tile.h
enum FruitType { ..., NewFruit };

// 2. Add color in tile.cpp
case FruitType::NewFruit: return { R, G, B, 255 };

// 3. Add to creation in board.cpp
FruitType types[] = { ..., FruitType::NewFruit };
```

**New Power-Up**:
```cpp
// 1. Enhance SpecialType enum
// 2. Implement match logic in Board::processMatches
// 3. Add rendering in Tile::render
// 4. Add particle effect in ParticleSystem
```

**New Game State**:
```cpp
// 1. Add to GameState enum
// 2. Implement handling in Game::update
// 3. Add rendering in Game::render
// 4. Add transitions via Game state logic
```

## Performance Targets

- **FPS**: 60 (locked)
- **Frame Time**: 16.67ms
- **Memory**: < 50MB
- **Binary Size**: < 500KB (with graphics)
- **Startup Time**: < 2 seconds

## Scalability

### Current Limits
- Board: 8x8 (can scale to 10x10 with minor changes)
- Level: 999 (easily extensible)
- Score: 2^31-1 (int based)

### Optimization Points
- Batch rendering for tiles
- GPU particle system
- Level streamer for large maps
- Physics engine integration potential

## Testing Recommendations

### Unit Tests
```cpp
// Test match detection
TEST(BoardTest, DetectHorizontalMatch)

// Test gravity
TEST(BoardTest, ApplyGravity)

// Test tile animation
TEST(TileTest, AnimationProgress)
```

### Integration Tests
```cpp
// Test game loop
TEST(GameTest, GameLoopExecution)

// Test level progression
TEST(GameTest, LevelCompletion)
```

## Documentation

### Code Comments
- Rationale for complex algorithms
- Non-obvious design decisions
- Performance-sensitive sections

### Function Documentation
```cpp
/// Detects all matches on the board
/// @return true if matches found, false otherwise
bool Board::findMatches();
```

## Version History

- **v1.0**: Core game functional, graphics ready, framework complete
- **Road**:
  - Power-up system refinement
  - Multiplayer support
  - Leaderboard system
  - Mobile optimization

## License & Attribution

Educational project demonstrating professional game development practices.

---

For questions about specific components, see the inline code comments in each file's implementation.
