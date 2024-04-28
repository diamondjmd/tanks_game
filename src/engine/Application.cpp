#include "Application.h"

#include <SFML/Window/Event.hpp>
#include <iostream>

#include "../game/Player.h"
#include "../game/World.h"
#include "CacheManager.h"
#include "Painter.h"


Application::Application(const char* name, unsigned int width, unsigned int height)
    : window{sf::VideoMode (width, height),
             name,
             sf::Style::Titlebar | sf::Style::Close,
             sf::ContextSettings(0, 0, 4)} {
    
    //window.setFramerateLimit(144);
    window.setFramerateLimit(60);
    //window.setVerticalSyncEnabled(false);
}

void Application::run(World& world) {
    m_time = std::chrono::system_clock::now();
    m_totalTime = 0.;

    if (world.getCurrentPlayerName().empty()){
        std::cout << "current player is not available" << std::endl;
        return;
    }

    CacheManager::loadTexturesFrom("../resources/textures");
    m_time = std::chrono::system_clock::now();
  
    //Game loop
    while (window.isOpen()) {
        processEvents(world);
        updateWorld(world);
        drawWorld(world);
    }
}

void Application::processEvents(World& world){
    for (sf::Event event{}; window.pollEvent(event);) {
        if (event.type == sf::Event::EventType::Closed){    
            window.close();
        }
    }
    m_actions.update(window);
    world.getCurrentPlayer().update(world, m_actions);
}


void Application::updateWorld(World& world) {
    const auto currentTime = std::chrono::system_clock::now();
    const double deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - m_time).count();
    m_time = currentTime;
    m_totalTime += deltaTime;
    world.update(deltaTime);
}

void Application::drawWorld(const World& world) {
    Painter painter(window);
    world.show(painter);
}
