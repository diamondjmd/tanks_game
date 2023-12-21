#pragma once

#include "../engine/Rect.h"

class Obstacle: public Rect{
public:
    enum Type{
        BarricadeMetal,
        BarrelRust,
        BarrelRed,
        BarrelGreen,
        BarrelRedBlack,
        CrateMetal,
        CrateMetalSide,
        CrateWood,
        CrateWoodSide,
        FenceRed,
        FenceYellow,
        OilSpill,
        SandbagBeige,
        SandbagBeigeOpen,
        SandbagBrown,
        SandbagBrownOpen,
        TreeBrown,
        TreeBrownTwigs,
        TreeGreen,
        TreeGreenTwigs,
        Count
    };
    Obstacle();
    Obstacle(const Point<float>& position, const Point<float>& size, Type type = Type::TreeBrown, controls::Action rotation = controls::Action::Up);
    // Getters
    Type getType() const;
    // Setters
    void setType(Type type);
private:
    Type m_type{};
};