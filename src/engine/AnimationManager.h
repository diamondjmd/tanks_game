#pragma once

#include <vector>
#include "../game/Animation.h"

class AnimationManager{
public:
    enum Animate{
        Explosion,
        Shooting,
        Impact,
        Tracks,
        Count
    };

    AnimationManager();
    void createAnimation(Animate animation, Point<float> position, controls::Action rotation = controls::Action::Right);
    void update();
    void draw(Painter& painter, sf::Sprite& sprite) const;
    
private:
    std::vector<Animation> m_animations;
};