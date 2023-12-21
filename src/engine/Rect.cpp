#include "Rect.h"

// Constructors
Rect::Rect(const Point<float>& position, const Point<float>& size, const std::string& texture, 
            graphs::Color color, controls::Action rotation, bool collidable)

        :m_center{position}, m_size{size},m_rotation{rotation}, m_texture{texture}, 
        m_color{color} ,m_collidable{collidable} {}

Rect::Rect(float x, float y, float width, float height, const std::string& texture, 
            graphs::Color color , controls::Action rotation, bool collidable)
        : Rect{Point<float>{x,y},Point<float>{width, height},texture, color, rotation, collidable} {}

// Getters
bool Rect::isCollidable() const{
    return m_collidable;
}

bool Rect::isCollidingWith(const Rect& other) const {
    return m_center.x < other.m_center.x + other.m_size.x &&
           m_center.x + m_size.x > other.m_center.x &&
           m_center.y < other.m_center.y + other.m_size.y &&
           m_center.y + m_size.y > other.m_center.y;
}

graphs::Color Rect::getColor() const{
    return m_color;
}

Point<float> Rect::getPosition() const {
    return m_center;
}
 controls::Action Rect::getRotation() const {
    return m_rotation;
 }

Point<float> Rect::getSize() const{
    return m_size;
}

 std::string Rect::getTexture() const{
    return m_texture;
 }

// Setters
void Rect::setCollidable(bool collidable){
    m_collidable = collidable;
}

void Rect::setColor(const graphs::Color& color){
    m_color = color;
}

void Rect::setPosition(const Point<float>& position){
    m_center = position;
}

void Rect::setRotation(controls::Action rotation){
    m_rotation = rotation;
}
 
void Rect::setSize(const Point<float>& size){
    m_size = size;
}

// Operators
bool Rect::operator==(const Rect& other) const{
    return  other.m_center == m_center && 
            other.m_size == m_size && 
            other.m_texture == m_texture && 
            other.m_color == m_color && 
            other.m_rotation == m_rotation && 
            other.m_collidable == m_collidable;
}