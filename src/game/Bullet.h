#pragma once

#include "../engine/Rect.h"

class Painter;
namespace sf {class Sprite;}

class Bullet: public Rect {
    public:
        // Constructors
        Bullet(const Point<float> &position, const Point<float> &target, const std::string& shooterName, controls::Action rotation);
        Bullet(const Point<float> &position, const Point<float> &target, const std::string& shooterName, controls::Action rotation, const std::string& texture, const Point<float>& size, unsigned short speed, unsigned short damage, graphs::Color color);
        
        // Getters
        unsigned short getDamage() const;
        Point<float> getDirection() const;
        std::string getShooterName() const;
        unsigned short getSpeed () const;
        
        // Setters
        void setDamage(unsigned short damage);
        // void setDirection(const Point<float>& direction);
        void setSpeed(unsigned short speed);

        // Actions
        void draw(Painter& painter, sf::Sprite& sprite) const;
        bool hasPenetrated(const Rect& other) const;
        
    private:
        Point<float> m_direction;// normalized vector
        std::string m_shooterName{};
        unsigned short m_speed;
        unsigned short m_damage;
};
