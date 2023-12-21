#include "Tank.h"

#include "Bullet.h"
#include "../engine/Painter.h"

// constructors
Tank::Tank(const Point<float>& position, graphs::Color color)
    :Tank{position, Point<float>{40.f,40.f}, 1, 2.f, color, controls::Action::Right,
        1000, "../resources/textures/tanks.png"} {}

Tank::Tank(const Point<float>& position, const Point<float>& size, unsigned short level, 
         float speed, graphs::Color color, controls::Action rotation,
            unsigned short fireRate, const std::string &texture)
        : Rect{position, size, texture, color, rotation},
        m_movement{position}, m_level{level}, m_speed{speed},
        m_fireRate{fireRate}, m_fireCooldown{}{}

// Getters
bool Tank::canFire() const{
    return m_fireCooldown == 0;
}

unsigned short Tank::getFireCooldown() const{
    return m_fireCooldown;
}

unsigned short Tank::getFireRate () const{
    return m_fireRate;
}

Point<float> Tank::getMovement() const{
    return m_movement;
}


float Tank::getSpeed() const{
    return m_speed;
}

// Setters
void Tank::setFireRate (unsigned short fireRate){
    m_fireRate = fireRate;
}

void Tank::setMovement(const Point<float>& movement){
    m_movement = movement;
}

void Tank::setSpeed(float speed){
    m_speed = speed;
}

// actions
void Tank::draw(Painter& painter, sf::Sprite& sprite) const {
    painter.draw(*this, getColor(), getRotation(),sprite);
}

void Tank::decFireCooldown(){
    if(m_fireCooldown > 0){
        --m_fireCooldown;
    }
}

Bullet Tank::fire(const std::string& shooterName){
    m_fireCooldown = m_fireRate;
    const auto target  = Rect::getPosition() + rotatePoint(Point{2000.f, 2000.f}, Rect::getRotation() * 90.f);
    return Bullet{getTurretHeadPosition(), target,shooterName, getRotation()};
}

void Tank::move(const Point<float>& pos){
    Rect::setPosition(pos);
    m_movement = pos;
}

void Tank::tryMove(controls::Action direction, const Point<float>& distance){
    const auto RotatedDistance = rotatePoint(distance, direction * 90.f);
    m_movement += RotatedDistance * m_speed;
    if (direction != Rect::getRotation()) {
        rotate(direction);
    }
}

void Tank::rotate(controls::Action rotation){
    Rect::setRotation(rotation);
}

// helpers
Point<float> Tank::getTurretHeadPosition() const {
    return Rect::getPosition() + rotatePoint(Rect::getSize()/2.f, Rect::getRotation() * 90.f);
}

// Operators

bool Tank::operator==(const Tank& other) const{
    return Rect::operator==(other) &&
           m_level == other.m_level &&
           m_speed == other.m_speed &&
           m_fireRate == other.m_fireRate &&
           m_fireCooldown == other.m_fireCooldown;
}