#pragma once

#include "Point.h"
#include "Color.h"
#include <string>
#include "Controls.h"

class Rect{

public:
    // Constructors
    Rect() = default;
    Rect(const Point<float>& position, const Point<float>& size, const std::string& texture, 
        graphs::Color color = graphs::Color::Blue, controls::Action rotation = controls::Action::Right, bool collidable = true);
    Rect(float x, float y, float width, float height, const std::string& texture, 
        graphs::Color color, controls::Action rotation , bool collidable);
    
    // Getters
    bool isCollidable() const;
    bool isCollidingWith(const Rect& other) const;
    graphs::Color getColor() const;
    Point<float> getPosition() const;
    controls::Action getRotation() const;
    Point<float> getSize() const;
    std::string getTexture() const;
    
    // Setters
    void setCollidable(bool collidable);
    void setPosition(const Point<float>& position);
    void setRotation(controls::Action rotation);    
    void setSize(const Point<float>& size);
    void setTexture(const std::string& texture);
    void setColor(const graphs::Color& color);

    // Operators
    bool operator==(const Rect& other) const;
    
    // actions

private:
    Point<float> m_center{};
    Point<float> m_size{};
    controls::Action m_rotation{};
    std::string m_texture;
    graphs::Color m_color;
    bool m_collidable{};
};

