#include "game.h"
#include "board.h"
#include "ui.h"
#include "input_handler.h"
#include "particle_system.h"
#include "sound_manager.h"
#include "config.h"

Game::Game()
    : state(GameState::MENU), score(0), level(1), movesLeft(30), timeLeft(300.0f) {
    initialize();
}

Game::~Game() {
    cleanup();
}

void Game::initialize() {
    particleSystem = std::make_unique<ParticleSystem>();
    board = std::make_unique<Board>(8, 8, particleSystem.get());
    ui = std::make_unique<UI>(this);
    inputHandler = std::make_unique<InputHandler>(this);
    soundManager = std::make_unique<SoundManager>();

    // Set up input callbacks
    inputHandler->setMouseClickCallback([this](int x, int y) {
        // Handle tile selection
        int tileSize = 50;
        int boardX = x / tileSize;
        int boardY = y / tileSize;

        if (boardX >= 0 && boardX < board->getWidth() &&
            boardY >= 0 && boardY < board->getHeight()) {
            // Handle tile click
        }
    });
}

void Game::cleanup() {
    // Smart pointers handle cleanup
}

void Game::run() {
    float lastTime = 0.0f;

    while (!WindowShouldClose()) {
        float currentTime = GetFrameTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        update(deltaTime);
        render();
    }
}

void Game::update(float deltaTime) {
    inputHandler->update(deltaTime);
    board->update(deltaTime);
    ui->update(deltaTime);
    particleSystem->update(deltaTime);

    if (state == GameState::PLAYING) {
        updateTimer(deltaTime);

        if (movesLeft <= 0 || timeLeft <= 0) {
            setState(GameState::GAME_OVER);
            soundManager->playGameOverSound();
        }
    }
}

void Game::render() {
    BeginDrawing();
    ClearBackground(COLOR_BLACK);

    board->render();
    ui->render();
    particleSystem->render();

    EndDrawing();
}

void Game::nextLevel() {
    level++;
    movesLeft = 30 + level * 5;
    timeLeft = 300.0f + level * 30.0f;
    soundManager->playLevelCompleteSound();
}