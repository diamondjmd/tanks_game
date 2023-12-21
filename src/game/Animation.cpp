#include "Animation.h"

#include "../engine/Painter.h"

 Animation::Animation(const Point<float>& position, const std::string& texture, unsigned short numFrames, 
                        controls::Action rotation, const Point<float>& size, unsigned short frameSwichTime)
                        :Rect{position, size, texture, graphs::Color::Beige, rotation, false},
                         m_elapTime{},m_numFrames{numFrames}, m_frame{},m_frameSwichTime{frameSwichTime}, m_playing{true} {}

// getters
bool Animation::isPlaying() const{
    return m_playing;
}

// actions
void Animation::update() {
    if (m_playing) {
        ++m_elapTime;

        if (m_elapTime >= m_frameSwichTime) {
            m_elapTime = 0;

            if (m_frame < m_numFrames - 1) {
                ++m_frame;
            }else{
                m_playing = false;
            }
        }
    }
}

void Animation::draw(Painter& painter, sf::Sprite& sprite) const{
    painter.draw(*this,  m_frame, sprite);
}