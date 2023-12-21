#pragma once

#include "../engine/Rect.h"

class Painter;
namespace sf {class Sprite;}

class Animation: public Rect{
public:
    Animation(const Point<float>& position, const std::string& texture, unsigned short numFrames, 
    controls::Action rotation = controls::Action::Right, const Point<float>& size = Point<float>(40, 40), unsigned short frameSwichTime = 500);
    // Getters
    bool isPlaying() const;
    // Actions
    void draw(Painter& painter, sf::Sprite& sprite) const;
    void update();
private:
    std::size_t m_elapTime{}; // elapse time in ticks or iterations
    unsigned short m_numFrames{};
    unsigned short m_frame{};
    unsigned short m_frameSwichTime{};
    bool m_playing {true};

};