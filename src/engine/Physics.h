#pragma once

#include <unordered_map>
#include <string>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Point.h"

// Forward declarations
class Player;
class Bullet;
class Rect;
class Tank;
class AnimationManager;
class Obstacle;

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point<float>& worldSize);
    void update(std::unordered_map<std::string, Player>& players, std::vector<Bullet>& bullets, AnimationManager& animations, const std::vector<Obstacle>& obstacles, const size_t ticks);
  
  private:
    bool isCollidingWithBox(const Point<float>& position, Point<float> size) const;
    bool collidingWithObjs(const Rect& obj, const std:: string& playerName, const std::unordered_map<std::string, Player>& players, const std::vector<Obstacle>& obstacles) const;
    
    void move(std::unordered_map<std::string, Player>& players, const std::vector<Obstacle>& obstacles) const;
  
    void move(std::vector<Bullet>& bullets) const;
    void collideBullets(std::vector<Bullet>& bullets, std::unordered_map<std::string, Player>& players, const std::vector<Obstacle>& obstacles, AnimationManager& Animations) const;
    void processBulletCollisions(const Bullet& bullet, const std::string& playerName ,std::unordered_map<std::string, Player>& players, AnimationManager& animations) const;
 
  private:
    Point<float> m_worldSize;
    double m_timePerTick;
};
