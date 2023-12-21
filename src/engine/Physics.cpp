#include "Physics.h"
#include "../game/Bullet.h"
#include "../game/Obstacle.h"
#include "../game/Player.h" 

#include "AnimationManager.h"
#include "Rect.h"
#include <iostream>
Physics::Physics(double timePerTick) : m_timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point<float>& worldSize) {
    m_worldSize = worldSize;
}


void Physics::update(std::unordered_map<std::string, Player>& players, std::vector<Bullet>& bullets, AnimationManager& animations, const std::vector<Obstacle>& obstacles, const size_t ticks){
    for (size_t i = 0; i < ticks; ++i) {
        move(bullets);
        move(players, obstacles);
        collideBullets(bullets, players, obstacles, animations);
        animations.update();
    }
} 

void Physics::move(std::unordered_map<std::string, Player>& players,const std::vector<Obstacle>& obstacles) const {
    for (auto& [playerName, player]: players) {
        if(player.isAlive()){
            auto tank = player.getTank();
            tank.decFireCooldown();

            const auto startPos = tank.getPosition();
            const auto endPos = tank.getMovement() ;
            
            if (startPos != endPos){
                tank.move(endPos);

                //check collision
                if (isCollidingWithBox(endPos, tank.getSize())  ||
                    collidingWithObjs(tank, playerName, players, obstacles)){
                    tank.move(startPos);
                }
            }
            
            player.setTank(std::move(tank));
        }
    }
}

 void Physics::move(std::vector<Bullet>& bullets) const{
    for(auto &bullet: bullets){
        bullet.setPosition(bullet.getPosition() + bullet.getDirection() * bullet.getSpeed() * m_timePerTick);
    }
 }

  void Physics::collideBullets(std::vector<Bullet>& bullets, std::unordered_map<std::string, Player>& players, const std::vector<Obstacle>& obstacles, AnimationManager& animations) const{
        bool isDeleted;
        auto bullet = bullets.begin();
        
        while (bullet != bullets.end()){
            isDeleted = false;
            if (isCollidingWithBox(bullet->getPosition(), bullet->getSize())){
                bullet = bullets.erase(bullet);
                isDeleted = true;
            }else{
                // check collision with players
               for (auto& [playerName, player]: players) { 
                    if (player.isAlive() && 
                        playerName != bullet->getShooterName()){

                        if (bullet->hasPenetrated(player.getTank())){
                            processBulletCollisions(*bullet, playerName, players, animations);
                            
                            bullet = bullets.erase(bullet);
                            isDeleted = true;
                            break;
                        }
                    }
                }

                if (!isDeleted){
                    for (const auto& obstacle: obstacles) {
                        if (bullet->isCollidingWith(obstacle)) {
                            animations.createAnimation(AnimationManager::Animate::Impact, bullet->getPosition(),bullet->getRotation());
                            bullet = bullets.erase(bullet);
                            isDeleted = true;
                            break;
                        }
                    }
                }
            }

            if (!isDeleted){
                ++bullet;
            }
        }
 }

bool Physics::isCollidingWithBox(const Point<float>& position,  Point<float> size) const {
    size = size / 2.f;
    // Check if the tank's bounding box extends beyond the world boundaries
    bool isCollidingWithLeftBound = position.x - size.x< 0;
    bool isCollidingWithRightBound = position.x + size.x > m_worldSize.x;
    bool isCollidingWithTopBound = position.y - size.y< 0;
    bool isCollidingWithBottomBound = position.y + size.y > m_worldSize.y;
    // Determine if any of the bounding box edges are outside the world boundaries
    return isCollidingWithLeftBound || isCollidingWithRightBound || isCollidingWithTopBound || isCollidingWithBottomBound;
}

bool Physics::collidingWithObjs(const Rect& obj, const std:: string& playerName, const std::unordered_map<std::string, Player>& players, const std::vector<Obstacle>& obstacles) const{

    for (const auto& [currPlayerName, currPlayer]: players) {
        if (!currPlayer.isAlive() || playerName == currPlayerName) {
           continue;
        }

       if (currPlayer.getTank().isCollidingWith(obj)) {
            return true;
       }   
    }

    for (const auto& obstacle: obstacles) {
        if (obj.isCollidingWith(obstacle)) {
            return true;
        }
    }
    return false;
}

void Physics::processBulletCollisions(const Bullet& bullet, const std::string& playerName ,std::unordered_map<std::string, Player>& players, AnimationManager& animations) const{
    players[playerName].decHealth(bullet.getDamage());
    
    if(!players[playerName].isAlive()) {
        players[playerName].incDeaths();
        players[bullet.getShooterName()].incKills();
        animations.createAnimation(AnimationManager::Animate::Explosion,  players[playerName].getTank().getPosition());
    }else{
        animations.createAnimation(AnimationManager::Animate::Impact, bullet.getPosition(), bullet.getRotation());
    }
}
