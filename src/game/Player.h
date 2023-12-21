#pragma once 

#include <string>
#include "Tank.h"

// Forward declaration
class World;
class InputManager;
class Painter;

class Player {
    public:
        // Constructors
        Player() = default;
        Player(const std::string& name, const Tank& tank, unsigned short maxHealth = 100);
        
        // Getters
        std::size_t getDeaths() const;
        unsigned short getHealth() const;
        unsigned short getMaxHealth() const;

        std::size_t getKills() const;
        std::string getName() const;
        Tank getTank() const;
        bool isAlive() const;
        
        // Setters
        void setMaxHealth(unsigned short maxHealth);
        void setName(const std::string& name);
        void setTank(const Tank& tank);
        void setTank(Tank&& tank) noexcept;
        
        // Actions
        void incDeaths();
        void incKills();
        void draw(Painter& painter, sf::Sprite& sprite) const;
        void decHealth(unsigned short amount =10);
        void update(World& world, const InputManager& actions);
    
    private:
        Tank m_tank;
        std::string m_name;
        unsigned short m_maxHealth{};
        std::size_t m_kills;
        std::size_t m_deaths;
        unsigned short m_health{};
};