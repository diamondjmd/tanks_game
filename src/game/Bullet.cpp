#include "Bullet.h"

#include <cmath>
#include "../engine/Painter.h"

// Constructors
Bullet::Bullet(const Point<float> &position, const Point<float> &target, const std::string& shooterName, 
                controls::Action rotation)
            : Bullet{position, target, shooterName, rotation, 
                    "../resources/textures/bullets.png", 
                    Point<float>{5.f, 15.f}, 700, 20, graphs::Color::Blue} {}

Bullet::Bullet(const Point<float> &position, const Point<float> &target, const std::string& shooterName, 
                controls::Action rotation, const std::string& texture, const Point<float>& size, 
                unsigned short speed, unsigned short damage, graphs::Color color)
                            
                :Rect{position, size, texture, color, rotation}, 
                m_direction {normalize(target -  Rect::getPosition())}, // normalized vector
                m_shooterName{shooterName}, m_speed{speed}, m_damage{damage}{}

// Getters
unsigned short Bullet::getDamage() const{
    return m_damage;
}

Point<float> Bullet::getDirection() const {
    return m_direction;
}

std::string Bullet::getShooterName() const{
    return m_shooterName;
}

unsigned short Bullet::getSpeed () const{
    return m_speed;
}

// Setters
void Bullet::setDamage(unsigned short damage){
    m_damage = damage;
}

void Bullet::setSpeed(unsigned short speed){
    m_speed = speed;
}

//  Actions
void Bullet::draw(Painter& painter, sf::Sprite& sprite) const {
    painter.draw(*this, 0 , getRotation(), sprite);
}

  // check penetration with another rectangle
bool Bullet::hasPenetrated(const Rect& other) const {
        // Calculate the distance between the centers of the rectangles
        double distance = std::sqrt(std::pow(getPosition().x - other.getPosition().x, 2) + std::pow(getPosition().y - other.getPosition().y, 2));

        // Calculate the sum of half-widths for each rectangle
        double sumHalfWidths = (getSize().x + other.getSize().x) / 2;
        double sumHalfHeights = (getSize().y + other.getSize().y) / 2;

        // Check if the distance is less than the sum of half-widths and half-heights
        return distance < sumHalfWidths && distance < sumHalfHeights;
}