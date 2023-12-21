#include "Player.h" 
#include "World.h"
#include "../engine/InputManager.h"
#include "../engine/Painter.h"

// Constructors
Player::Player(const std::string& name, const Tank& tank, unsigned short maxHealth) 
    :m_tank{tank}, m_name{name}, m_maxHealth{maxHealth}, m_kills{}, m_deaths{}, m_health{maxHealth}{}

// Getters
std::size_t Player::getDeaths() const {
    return m_deaths;
}

unsigned short Player::getHealth() const{
    return m_health;
}

unsigned short Player::getMaxHealth() const{
    return m_maxHealth;
}

std::size_t Player::getKills() const {
    return m_kills;
}

std::string Player::getName() const { 
    return m_name;
}

Tank Player::getTank() const {
    return m_tank;
}

bool Player::isAlive() const {
    return m_health > 0;
}

// Setters
void Player::setMaxHealth(unsigned short maxHealth){
    m_maxHealth = maxHealth;
}

void Player::setName(const std::string& name){
    m_name = name;
}

void Player::setTank(const Tank& tank){
    m_tank = tank;
}

void Player::setTank(Tank&& tank) noexcept{
    m_tank = tank;
}

// Actions
void Player::incKills(){
    ++m_kills;
}

void Player::incDeaths(){
    ++m_deaths;
}

void Player::decHealth(unsigned short amount){
    if(m_health - amount > 0){
        m_health -= amount;  
    }else{
        m_health = 0;
    }
}

void Player::draw(Painter& painter, sf::Sprite& sprite) const {
    painter.draw(*this, sprite);
}

void Player::update(World& world, const InputManager& actions){

    if (actions.isActionPressed(controls::Action::Right)) {
        m_tank.tryMove(controls::Action::Right);
        world.addAnimation(AnimationManager::Animate::Tracks, m_tank.getPosition(), controls::Action::Right);
    }else if (actions.isActionPressed(controls::Action::Down)) {
       world.addAnimation(AnimationManager::Animate::Tracks, m_tank.getPosition(), controls::Action::Down);
       m_tank.tryMove(controls::Action::Down);

    }else if (actions.isActionPressed(controls::Action::Left)) {
        world.addAnimation(AnimationManager::Animate::Tracks, m_tank.getPosition(), controls::Action::Left);
        m_tank.tryMove(controls::Action::Left);
    }else if (actions.isActionPressed(controls::Action::Up)) {
        world.addAnimation(AnimationManager::Animate::Tracks, m_tank.getPosition(), controls::Action::Up);
        m_tank.tryMove(controls::Action::Up);
    }

    if (actions.isActionPressed(controls::Action::Fire) && m_tank.canFire()){
        // world.addBullet(m_tank.fire(actions.getMousePosition()));

        auto bullet = m_tank.fire(m_name);
        world.addAnimation(AnimationManager::Animate::Shooting, bullet.getPosition(), bullet.getRotation());
        world.addBullet(std::move(bullet));
    }
}







