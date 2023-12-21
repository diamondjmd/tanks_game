#pragma once

#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Point.h"

namespace sf { class RenderWindow;};
class Rect;
class Player;
class Animation;
class Map;

class Painter {
  public:

    Painter(sf::RenderWindow& window);
    ~Painter();
    
    void draw(const Point<float>& pos, const std::string& texture, const Point<float> &scaleTo = Point(1.f, 1.f)) const;
    void draw(const Rect& obj, unsigned short row, unsigned short col, sf::Sprite& sprite ) const; 
    void draw(const Player& player, sf::Sprite& sprite) const;
    void draw(const Animation& animation, unsigned short frame, sf::Sprite& sprite) const;
  
  private:
    sf::Vector2f toVector(const Point<float>& point) const;

  private:
    sf::RenderWindow& window;
};
