#pragma once

#include <string>
#include "../engine/Rect.h"

// Forward declarations
class Painter;
class Bullet;
template<typename T> class Point;
namespace sf {class Sprite;}

class Tank : public Rect{
public:
    // constructors
    Tank() = default; 
    Tank(const Point<float>& position, graphs::Color color = graphs::Color::Blue);
    Tank(const Point<float>& position, const Point<float>& size, unsigned short level,
        float speed, graphs::Color color, controls::Action rotation, unsigned short fireRate,
        const std::string &texture);

    // getters
    bool canFire() const;
    unsigned short getFireCooldown() const;
    unsigned short getFireRate () const;
    Point<float> getMovement() const;
    float getSpeed() const;

    // Setters
    void setFireRate (unsigned short fireRate);
    void setHealth(unsigned short health);
    void setMaxHealth(unsigned short maxHealth);
    void setMovement(const Point<float>& movement);
    void setSpeed(float speed);

    // actions
    void draw(Painter& painter, sf::Sprite& sprite) const;
    void decFireCooldown();
    Bullet fire(const std::string& shooterName);
    void move(const Point<float>& pos);
    void tryMove(controls::Action direction, const Point<float>& distance = Point<float>{1.f, 1.f});
    void rotate(controls::Action rotation);

    // Operators
    bool operator==(const Tank& other) const;


private:
    //helpers
    Point<float> getTurretHeadPosition() const;

private:
    Point<float> m_movement;
    unsigned short m_level{}; 
    float m_speed{};
    unsigned short m_fireRate{}; //ticks or frames to wait
    unsigned short m_fireCooldown{}; //ticks or frames left
};
