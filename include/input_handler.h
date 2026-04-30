<<<<<<< HEAD
#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "config.h"
#include <functional>

class InputHandler {
public:
    InputHandler();
    ~InputHandler();
    
    void update();
    
    // Input detection
    bool isMouseClicked() const { return mouseClicked; }
    Vector2 getMousePosition() const { return mousePos; }
    bool isKeyPressed(int key) const;
    
    // Callbacks
    using MouseClickCallback = std::function<void(float, float)>;
    using KeyPressCallback = std::function<void(int)>;
    
    void setMouseClickCallback(MouseClickCallback cb) { onMouseClick = cb; }
    void setKeyPressCallback(KeyPressCallback cb) { onKeyPress = cb; }
    
private:
    Vector2 mousePos;
    bool mouseClicked;
    
    MouseClickCallback onMouseClick;
    KeyPressCallback onKeyPress;
};

#endif // INPUT_HANDLER_H
=======
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
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
