#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <chrono>
#include "InputManager.h"

class InputManager;
class World;

class Application {
  public:

    Application(const char* name, unsigned int width, unsigned int height);
    void run(World& world);

  private:
    void processEvents(World& world);
    void updateWorld(World& world);
    void drawWorld(const World& world);

  private:
    
    sf::RenderWindow window;
    std::chrono::system_clock::time_point m_time;
    InputManager m_actions;
    double m_totalTime{};
};
