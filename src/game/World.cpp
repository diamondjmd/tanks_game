#include "World.h"
#include "../engine/Painter.h"
#include "Player.h"

#include <SFML/Graphics/Sprite.hpp>
#include "../engine/CacheManager.h"


// Duration of one simulation tick.
// Should not be changed
static constexpr double timePerTick = 0.001;

World::World(const std::string& mapPath):m_map{mapPath}{
    m_worldSize = m_map.getWorldSize();
    initWorld();
}

// Constructors
World::World(const Point<float>& worldSize)
    : m_worldSize{worldSize}, m_current_playerName{}, m_map{worldSize,Point{40.f, 40.f}}{
    
    initWorld();
}

// Getters
Player& World::getCurrentPlayer(){
    return m_players.at(m_current_playerName);
}

std::string World::getCurrentPlayerName() const {
    return m_current_playerName;
}

const std::vector<Obstacle>& World::getObstacles() const{
    return m_map.getObstacles();
}

Player& World::getPlayer(const std::string& playerName){
    return m_players.at(playerName);
}

// Setters
void World::setCurrentPlayerName(const std::string& name) {
    m_current_playerName = name;
}

// Actions
void World::addAnimation(AnimationManager::Animate animation, Point<float> position, controls::Action rotation){
    m_animationManager.createAnimation(animation, position, rotation);
}
void World::addBullet(const Bullet& bullet){
    m_bullets.push_back(bullet);
}

void World::addBullet(Bullet&& bullet) noexcept{
    m_bullets.push_back(std::move(bullet));
}

bool World::addPlayer(const Player& player) {
    const auto& pair = m_players.try_emplace(player.getName(), player);
   return pair.second? true : false;
}

// Displays the state of the world
void World::show(Painter& painter) const {
    m_map.draw(painter);

    sf::Sprite sprite;

    if (m_bullets.size()){
        sprite.setTexture(CacheManager::getTexture(m_bullets[0].getTexture()));
        
        for (const auto& bullet: m_bullets) {
            bullet.draw(painter, sprite);   
        }
    }

    if (!m_players.empty()){
        const auto& anyPlayer = m_players.begin()->second;  
        sprite.setTexture(CacheManager::getTexture(anyPlayer.getTank().getTexture()));
        
        for (const auto& pairPlayer: m_players) {
            if (pairPlayer.second.isAlive()){
                pairPlayer.second.draw(painter, sprite);
            }
        }
    }

    m_animationManager.draw(painter, sprite);
}

void World::update(double deltaTime) {
    deltaTime += restTime;
    const auto ticks = static_cast<size_t>(std::floor(deltaTime / timePerTick));
    restTime = deltaTime - double(ticks) * timePerTick;
    m_physics.update(m_players, m_bullets, m_animationManager, getObstacles() , ticks); 
}



void World::addStaticBots(){

    //enemy player test:
    Player enemy{"enemy", Tank{Point<float>{680.0f, 260.f}, graphs::Color::BeigeOutline}};
    addPlayer(enemy);
   
    Player enemy2{"enemy2", Tank{Point<float>{680.0f, 57.f}, graphs::Color::Blue}};
    addPlayer(enemy2);

    Player enemy3{"enemy3", Tank{Point<float>{680.0f, 900.f}, graphs::Color::Beige}};
    addPlayer(enemy3);


    Player enemy4{"enemy4", Tank{Point<float>{100.0f, 900.f}, graphs::Color::Black}};
    addPlayer(enemy4);
    
    Player enemy5{"enemy5", Tank{Point<float>{90.0f, 60.f}, graphs::Color::RedOutline}};
    addPlayer(enemy5);
}

void World::initWorld(){
    m_physics.setWorldBox(m_worldSize);
    m_bullets.reserve(200);
    m_players.reserve(5);

    addStaticBots();

}
