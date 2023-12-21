#include "InputManager.h"


InputManager::InputManager() {
    // Initialize input state variables
    for (int i = 0; i < controls::Action::Count; ++i) {
        actionStates[i] = false;
    }
}

void InputManager::update(sf::RenderWindow& window) {
    // Update mouse position
    //mousePosition = sf::Mouse::getPosition(window);
    
    // Check for keyboard and mouse input events
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
        if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i)) {
            handleKeyPress((sf::Keyboard::Key)i);
        } else {
            handleKeyRelease((sf::Keyboard::Key)i);
        }
    }

    // Check for mouse button clicks
    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //     actionStates[controls::Action::Fire] = true;
    // } else {
    //     actionStates[controls::Action::Fire] = false;
    // }
}

bool InputManager::isActionPressed(controls::Action action) const {
    return actionStates[action];
}

// Point<float> InputManager::getMousePosition() const {
//     return Point(mousePosition.x, mousePosition.y);
// }

void InputManager::handleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::W:
            actionStates[controls::Action::Up] = true;
            break;
        case sf::Keyboard::S:
            actionStates[controls::Action::Down] = true;
            break;
        case sf::Keyboard::A:
            actionStates[controls::Action::Left] = true;
            break;
        case sf::Keyboard::D:
            actionStates[controls::Action::Right] = true;
            break;
        case sf::Keyboard::Space:
            actionStates[controls::Action::Fire] = true;
            break;
         case sf::Keyboard::Escape:
            actionStates[controls::Action::Close] = true;
            break;
           
    }
}

void InputManager::handleKeyRelease(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::W:
            actionStates[controls::Action::Up] = false;
            break;
        case sf::Keyboard::S:
            actionStates[controls::Action::Down] = false;
            break;
        case sf::Keyboard::A:
            actionStates[controls::Action::Left] = false;
            break;
        case sf::Keyboard::D:
            actionStates[controls::Action::Right] = false;
            break;
        case sf::Keyboard::Space:
            actionStates[controls::Action::Fire] = false;
            break;
        case sf::Keyboard::Escape:
            actionStates[controls::Action::Close] = false;
            break;
    }
}