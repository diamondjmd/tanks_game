#pragma once

#include "../engine/Rect.h"

class Painter;

class Tile : public Rect{
public:
enum Type{
    Grass,
    GrassSandTransition,
    GrassDirtTransition,
    Sand,
    Dirt,
    Count

};
    Tile() = default;
    Tile(const Point<float>& position, const Point<float>& size, Type type = Type::Grass, controls::Action rotation = controls::Action::Right);
    
    // Getters
    bool isOccupied() const;
    Type getType() const;
    
    // Setters
    void setOccupied(bool occupied);
    void setType(Type type);
    
    // Actions
  
private:
    Type m_type{};
    bool m_occupied{};
};


