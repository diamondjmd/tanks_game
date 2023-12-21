#pragma once

#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../engine/Rect.h"
#include "Tile.h"
#include "Obstacle.h"
#include <nlohmann/json.hpp>


class Map{
public:
    Map(const std::string& mapPath);
    Map(const Point<float>& worldSize, const Point<float>& tileSize);

    // Getters
    std::vector<Obstacle>& getObstacles();
    const std::vector<Obstacle>& getObstacles() const;
    std::vector<std::vector<Tile>>& getTiles();
    const std::vector<std::vector<Tile>>& getTiles() const;
    Point<float> getWorldSize() const;
    
    // Actions
    void draw(Painter& painter) const;

private:
    void initMap (const Point<float>& mapSize, const Point<float>& tileSize);
    bool hasAllKeys(const nlohmann::json& json, const std::vector<std::string>& keys) const;


private:
    Point<float> m_worldSize{};
    Point<float> m_tileSize{};
    unsigned short m_rows{};
    unsigned short m_columns{};
    sf::Texture m_tileTexture;
    sf::Texture m_obstacleTexture;
    mutable sf::Sprite m_tileSprite;
    mutable sf::Sprite m_obstacleSprite;
    std::vector<std::vector<Tile>> m_tiles;
    std::vector<Obstacle> m_obstacles;
};