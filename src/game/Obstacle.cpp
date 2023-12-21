#include "Obstacle.h"
Obstacle::Obstacle():  Rect{Point<float>{}, Point<float>{}, "../resources/textures/map/obstacles.png", graphs::Color::Blue, controls::Action::Up}{}
Obstacle::Obstacle(const Point<float>& position, const Point<float>& size, Type type, controls::Action rotation)
: Rect{position, size, "../resources/textures/map/obstacles.png", graphs::Color::Blue, rotation},
      m_type{type} {}

// Getters
Obstacle::Type Obstacle::getType() const{
    return m_type;
}

// Setters
void Obstacle::setType(Type type){
    m_type = type;
}