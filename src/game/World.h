#pragma once

#include "../engine/Physics.h"
#include "../engine/AnimationManager.h"

#include "Bullet.h"
#include "Map.h"
#include <unordered_map>
#include <vector>

class Painter;
class Player;


class World {
  public:
    // Constructor
    World(const std::string& mapPath);
    World(const Point<float>& worldSize);

    // Getters
    Player& getCurrentPlayer();
    std::string getCurrentPlayerName() const;
    const std::vector<Obstacle>& getObstacles() const;
    Player& getPlayer(const std::string& playerName);

    //Setters
    void setCurrentPlayerName(const std::string& name);
    
    // Actions
    void addAnimation(AnimationManager::Animate animation, Point<float> position, controls::Action rotation = controls::Action::Right);
    void addBullet(const Bullet& bullet);
    void addBullet(Bullet&& bullet) noexcept;
    bool addPlayer(const Player& player);
    void show(Painter& painter) const;
    //void update(double time);
    //void update();
    void update(double deltaTime);

  private:
    void addStaticBots();
    void initWorld();

  private:
    // The world boundaries are set by the corners of the rectangle
    Point<float> m_worldSize;
  
    // Physics engine object
    Physics m_physics;
    AnimationManager m_animationManager;
    std::string m_current_playerName{};
    std::unordered_map<std::string, Player> m_players;
    std::vector<Bullet> m_bullets;
    Map m_map;

 

    // The length of the length of time that was not
    // taken into account in the previous simulation. See update implementation
    double restTime = 0.;
};
