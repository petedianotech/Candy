#include "input_handler.h"
#include "game.h"
#include "config.h"

InputHandler::InputHandler(Game* g) : game(g), mousePressed(false) {
}

InputHandler::~InputHandler() = default;

void InputHandler::update(float deltaTime) {
    handleMouseInput();
    handleKeyboardInput();
}

void InputHandler::handleMouseInput() {
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (IsMouseButtonPressed(0)) { // Left mouse button
        if (mouseClickCallback) {
            mouseClickCallback(mouseX, mouseY);
        }
    }
}

void InputHandler::handleKeyboardInput() {
    if (IsKeyPressed(27)) { // Escape key
        if (game->getState() == GameState::PLAYING) {
            game->setState(GameState::PAUSED);
        } else if (game->getState() == GameState::PAUSED) {
            game->setState(GameState::PLAYING);
        }
    }

    if (IsKeyPressed(32)) { // Space key
        if (game->getState() == GameState::MENU) {
            game->setState(GameState::PLAYING);
        }
    }
}