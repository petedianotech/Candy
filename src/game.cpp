#include "game.h"
#include "config.h"
#include <cmath>

Game::Game() 
    : state(GameState::Playing), currentLevel(1), score(0), 
      targetScore(500), moves(20), levelTime(300), running(true) {
}

Game::~Game() {
}

void Game::init() {
    board = std::make_unique<Board>();
    inputHandler = std::make_unique<InputHandler>();
    particleSystem = std::make_unique<ParticleSystem>();
    ui = std::make_unique<UI>();
    soundManager = std::make_unique<SoundManager>();
    
    // Initialize components
    board->init();
    ui->init();
    soundManager->init();
    
    // Set up board scoring callback
    board->setOnScoreCallback([this](int pts) {
        score = pts;
        if (soundManager) {
            soundManager->playMatchSound();
        }
    });
    
    // Set up input handling
    inputHandler->setMouseClickCallback([this](float mouseX, float mouseY) {
        // Convert mouse position to board coordinates
        const float boardX = 50;
        const float boardY = 150;
        const int tileSize = Board::TILE_SIZE;
        const int padding = Board::BOARD_PADDING;
        
        int col = (int)((mouseX - boardX - padding) / tileSize);
        int row = (int)((mouseY - boardY - padding) / tileSize);
        
        if (board->isValidMove(row, col)) {
            board->selectTile(row, col);
        }
    });
}

void Game::update(float dt) {
    if (!running) return;
    
    handleInput(dt);
    
    switch (state) {
        case GameState::Playing:
            updateGame(dt);
            break;
            
        case GameState::Paused:
            // Only handle resume input
            break;
            
        case GameState::LevelComplete:
            if (IsKeyPressed(KEY_SPACE)) {
                nextLevel();
            }
            break;
            
        case GameState::GameOver:
            if (IsKeyPressed(KEY_SPACE)) {
                resetLevel();
                state = GameState::Playing;
            }
            break;
            
        default:
            break;
    }
    
    // Update all systems
    board->update(dt);
    particleSystem->update(dt);
    inputHandler->update();
}

void Game::render() {
    renderGame();
    
    // Draw UI
    ui->render(score, moves, targetScore, currentLevel, levelTime);
    
    // Draw game state overlays
    switch (state) {
        case GameState::Paused:
            ui->showPause();
            break;
            
        case GameState::LevelComplete:
            ui->showLevelComplete();
            break;
            
        case GameState::GameOver:
            ui->showGameOver();
            break;
            
        default:
            break;
    }
    
    // Render particles on top
    particleSystem->render();
}

bool Game::isRunning() const {
    return running;
}

void Game::handleInput(float dt) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        running = false;
    }
    
    if (IsKeyPressed(KEY_P)) {
        if (state == GameState::Playing) {
            state = GameState::Paused;
        } else if (state == GameState::Paused) {
            state = GameState::Playing;
        }
    }
}

void Game::updateGame(float dt) {
    levelTime -= dt;
    
    // Update board
    board->update(dt);
    
    // Check for level complete
    if (score >= targetScore) {
        state = GameState::LevelComplete;
        soundManager->playLevelCompleteSound();
    }
    
    // Check for game over
    if (moves <= 0 && score < targetScore) {
        state = GameState::GameOver;
    }
    
    // Time limit
    if (levelTime <= 0) {
        state = GameState::GameOver;
    }
}

void Game::renderGame() {
    // Draw game board background
    DrawRectangle(30, 140, 840, 420, {220, 220, 220, 255});
    DrawRectangleLines(30, 140, 840, 420, DARKGRAY);
    
    // Render board
    board->render();
}

void Game::checkLevelComplete() {
    if (score >= targetScore) {
        state = GameState::LevelComplete;
    }
}

void Game::nextLevel() {
    currentLevel++;
    targetScore += 200;
    moves = 20 + (currentLevel - 1) * 5;
    levelTime = 300;
    score = 0;
    board->resetScore();
    board->init();
    state = GameState::Playing;
}

void Game::resetLevel() {
    moves = 20;
    levelTime = 300;
    score = 0;
    board->resetScore();
    board->init();
    state = GameState::Playing;
}
