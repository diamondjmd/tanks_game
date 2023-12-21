#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Controls.h"


class InputManager {
    public:
        InputManager();
        void update(sf::RenderWindow& window);
        bool isActionPressed(controls::Action action) const;
        //Point<float> getMousePosition() const;

    private:
        void handleKeyPress(sf::Keyboard::Key key);
        void handleKeyRelease(sf::Keyboard::Key key);
        
        //members
        bool actionStates [controls::Action::Count];
        // Store the mouse position
        //sf::Vector2i mousePosition;
};
