#pragma once

#include <vector>
#include <memory>
#include "config.h"

class Board;
class UI;
class InputHandler;
class ParticleSystem;
class SoundManager;

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    LEVEL_COMPLETE,
    GAME_OVER
};

class Game {
public:
    Game();
    ~Game();

    void run();
    void update(float deltaTime);
    void render();

    // Game state
    GameState getState() const { return state; }
    void setState(GameState newState) { state = newState; }

    // Scoring
    int getScore() const { return score; }
    void addScore(int points) { score += points; }

    // Level management
    int getLevel() const { return level; }
    void nextLevel();

    // Moves
    int getMovesLeft() const { return movesLeft; }
    void useMove() { if (movesLeft > 0) movesLeft--; }

    // Timer
    float getTimeLeft() const { return timeLeft; }
    void updateTimer(float deltaTime) { timeLeft -= deltaTime; }

private:
    GameState state;
    std::unique_ptr<Board> board;
    std::unique_ptr<UI> ui;
    std::unique_ptr<InputHandler> inputHandler;
    std::unique_ptr<ParticleSystem> particleSystem;
    std::unique_ptr<SoundManager> soundManager;

    int score;
    int level;
    int movesLeft;
    float timeLeft;

    void initialize();
    void cleanup();
};