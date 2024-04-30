#include "Painter.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Rect.h"
#include "CacheManager.h"
#include "../game/Animation.h"
#include "../game/Player.h"
#include "../game/Map.h"


Painter::Painter(sf::RenderWindow& window) :window{window} {
    window.clear();
}

Painter::~Painter() {
    window.display();
}

void Painter::draw(const Point <float>& pos, const std::string& texture, const Point<float>& scaleTo) const{
    auto textu = CacheManager::getTexture(texture);
    sf::Sprite sprite;
    sprite.setTexture(textu);
    sprite.setPosition(toVector(pos));
    sprite.scale(toVector(scaleTo));
    window.draw(sprite);
}

void Painter::draw(const Rect& obj, unsigned short row, unsigned short col, sf::Sprite& sprite ) const{
    auto width = static_cast<int>(obj.getSize().x);
    auto height = static_cast<int>(obj.getSize().y);
    int maxWidth = std::max(width, height);
 
    sf::IntRect textureRect(col * maxWidth, row * maxWidth , maxWidth, maxWidth);
    
    sprite.setOrigin(width/ 2.f, height / 2.f);
    sprite.setTextureRect(textureRect);
    sprite.setPosition(toVector(obj.getPosition()));

    window.draw(sprite);
}

//draw the Player
void Painter::draw(const Player& player, sf::Sprite& sprite) const{
    auto tank = player.getTank();
    draw(tank, tank.getColor(),tank.getRotation() ,sprite);

    sf::RectangleShape healthBar;
    auto origin = toVector(tank.getSize() / 2.f);

    // draw the health bar
    const float healthRatio =  player.getHealth() / static_cast<float>(player.getMaxHealth()) * tank.getSize().x;
    auto healthPercent = static_cast<int>(player.getHealth()  *100.0 / player.getMaxHealth());

    if (healthPercent > 70) {
        healthBar.setFillColor(sf::Color::Green);
    } else if (healthPercent <= 70 && healthPercent > 40) {
       healthBar.setFillColor(sf::Color(255,215,0));
    } else {
        healthBar.setFillColor(sf::Color::Red);
    }

    const auto offsetPos = rotatePoint(Point<float>{1.f, 1.f}, tank.getRotation() * 90.f);
    healthBar.setSize(sf::Vector2f(8, healthRatio));
    healthBar.setOrigin(origin);
    healthBar.setPosition(toVector(tank.getPosition() - (offsetPos * 20.f)));
    healthBar.setRotation(tank.getRotation() * 90.f );

    // User Name
    sf::Text text;
    text.setFont(CacheManager::getFont("../resources/fonts/Roboto/Roboto-Bold.ttf"));
    text.setString(player.getName().substr(0, 7));
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    text.setOrigin(origin);
    text.setPosition(healthBar.getPosition() - (toVector(offsetPos* 20.f)));
    text.setRotation(healthBar.getRotation() +  90.f);

    window.draw(healthBar);
    window.draw(text);

    // draw the fire bar
    auto getFireCooldown = tank.getFireCooldown();
    if (getFireCooldown){
        sf::RectangleShape fireBar;
        const float fireRatio =  tank.getFireCooldown() / static_cast<float>(tank.getFireRate()) * tank.getSize().x;
        fireBar.setSize(sf::Vector2f(8, fireRatio));
        fireBar.setFillColor(sf::Color::Blue);
        fireBar.setOrigin(origin);
        fireBar.setPosition( healthBar.getPosition() - toVector(offsetPos * 8.f));
        fireBar.setRotation(healthBar.getRotation());
        window.draw(fireBar);
    }
}

 void Painter::draw(const Animation& animation, unsigned short frame, sf::Sprite& sprite) const{
    auto width = static_cast<int>(animation.getSize().x);
    auto height = static_cast<int>(animation.getSize().y);
    int maxWidth = std::max(width, height);

    sf::IntRect textureRect(frame * maxWidth, animation.getRotation() * maxWidth, maxWidth, maxWidth);
    sprite.setOrigin(width/ 2.f, height / 2.f);
    sprite.setTextureRect(textureRect);
    sprite.setPosition(toVector(animation.getPosition()));
    window.draw(sprite);
 }

sf::Vector2f Painter::toVector(const Point<float> & point) const {
    return {float(point.x), float(point.y)};
}

