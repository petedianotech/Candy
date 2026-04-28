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
