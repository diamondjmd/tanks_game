#include "Tile.h"

Tile::Tile(const Point<float>& position, const Point<float>& size, Type type , controls::Action rotation)
    : Rect{position, size, "../resources/textures/map/tiles.png", graphs::Blue, rotation, false},
      m_type{type}, m_occupied{false} {}


// Getters
bool Tile::isOccupied() const{
    return m_occupied;
}

Tile::Type Tile::getType() const{
    return m_type;
}
    
// Setters
void Tile::setOccupied(bool value){
    m_occupied = value;
}
void Tile::setType(Tile::Type type){
    m_type = type;
}
    
// Actions
