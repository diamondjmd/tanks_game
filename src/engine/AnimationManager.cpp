#include "AnimationManager.h"

#include <SFML/Graphics/Sprite.hpp>
#include "../engine/CacheManager.h"



AnimationManager::AnimationManager(){
    m_animations.reserve(20);
}

void AnimationManager::draw(Painter& painter, sf::Sprite& sprite) const{
   for(auto& animation : m_animations){
        sprite.setTexture(CacheManager::getTexture(animation.getTexture()));
        animation.draw(painter, sprite);
    }
}

 void AnimationManager::update(){
    for(auto animation = m_animations.begin(); animation != m_animations.end(); ){
        if (animation->isPlaying()){
            animation->update();
            ++animation;
        }else{
            animation = m_animations.erase(animation);
        }
    }
 }

void AnimationManager::createAnimation(Animate animation, Point<float> position, controls::Action rotation){
    switch (animation){
        case Animate::Explosion:
            m_animations.push_back(
                Animation{position,"../resources/textures/animations/explosion.png", 8, rotation, Point<float>{256.f,256.f}, 70}
        ); break;
        case Animate::Shooting:
            m_animations.push_back(
                Animation{position,"../resources/textures/animations/fireShot.png", 5, rotation, Point<float>{128.f, 128.f}, 30}
        ); break;
        case Animate::Impact:
            m_animations.push_back(
                Animation{position,"../resources/textures/animations/impact.png", 4, rotation, Point<float>{256.f, 256.f}, 50}
        ); break;
        
        case Animate::Tracks:
            m_animations.push_back(
                Animation{position,"../resources/textures/animations/tracks.png", 4, rotation, Point<float>{40.f, 40.f}, 5}
        ); break;
    }
}