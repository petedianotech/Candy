#pragma once

#include <functional>
#include "config.h"

class Game;

class InputHandler {
public:
    InputHandler(Game* game);
    ~InputHandler();

    void update(float deltaTime);

    using MouseClickCallback = std::function<void(int x, int y)>;
    void setMouseClickCallback(MouseClickCallback callback) { mouseClickCallback = callback; }

private:
    Game* game;
    MouseClickCallback mouseClickCallback;
    bool mousePressed;

    void handleMouseInput();
    void handleKeyboardInput();
};