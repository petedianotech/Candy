#include "input_handler.h"

InputHandler::InputHandler() 
    : mousePos({0, 0}), mouseClicked(false) {
}

InputHandler::~InputHandler() {
}

void InputHandler::update() {
    mousePos = GetMousePosition();
    mouseClicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    
    if (onMouseClick && mouseClicked) {
        onMouseClick(mousePos.x, mousePos.y);
    }
    
    // Check for key presses
    for (int key = 0; key < 512; ++key) {
        if (IsKeyPressed(key)) {
            if (onKeyPress) {
                onKeyPress(key);
            }
        }
    }
}

bool InputHandler::isKeyPressed(int key) const {
    return IsKeyPressed(key);
}
