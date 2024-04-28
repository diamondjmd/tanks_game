#include "Map.h"

#include <iostream>
#include <fstream>
#include "../engine/Painter.h"


 Map::Map(const std::string& mapPath){
    using json = nlohmann::json;
    
    std::ifstream file(mapPath);
    json mapData;
    file >> mapData;
    file.close();
    
    
    initMap(Point<float>{mapData["worldSize"]["x"].get<float>(), mapData["worldSize"]["y"].get<float>()},
            Point<float>{mapData["tileSize"]["x"].get<float>(), mapData["tileSize"]["y"].get<float>()}
    );

    Tile::Type tileType;
    controls::Action rotation;

    for (unsigned short row = 0; row < m_rows; ++row) {
        for (unsigned short col = 0; col < m_columns; ++col) {

            tileType = static_cast<Tile::Type>(mapData["tiles"][row][col][0].get<int>());
            rotation = static_cast<controls::Action>(mapData["tiles"][row][col][1].get<int>());
            m_tiles[row][col] = Tile{
                                    Point<float>{static_cast<float>(col * m_tileSize.x),static_cast<float>(row * m_tileSize.y)},
                                    Point<float>(static_cast<float>(m_tileSize.x),static_cast<float>(m_tileSize.y)),
                                    tileType,
                                    rotation
                                };
        }
    }

    if (mapData.contains("obstacles") &&
        mapData["obstacles"].contains("quantity")){
        int quantity = mapData["obstacles"]["quantity"].get<int>();

        for (unsigned short i = 0; i < quantity && i < m_rows * m_columns / 2; ++i){
            const json& jsonObstacle = mapData["obstacles"]["list"][i];
            Obstacle obstacle{};

            //parsing

            if (hasAllKeys(jsonObstacle, {"row", "col", "width", "height", "type", "rotation"})){
  
                auto row = jsonObstacle["row"].get<unsigned short>();
                auto col = jsonObstacle["col"].get<unsigned short>();

                if ( row < m_rows && col < m_columns &&
                    !m_tiles[row][col].isOccupied() ){
                    obstacle.setPosition(m_tiles[row][col].getPosition());
                }else{ 
                    continue;
                }

                auto type = static_cast<Obstacle::Type>(jsonObstacle["type"].get<int>()); 
                if (type < Obstacle::Type::Count){
                    obstacle.setType(type);
                }else{ 
                    continue;
                }

                obstacle.setSize(Point<float>{jsonObstacle["width"].get<float>(), 
                                            jsonObstacle["height"].get<float>()}
                                );

                auto rotation = static_cast<controls::Action>(jsonObstacle["rotation"].get<int>()); 
                
                obstacle.setRotation((rotation < controls::Action::Up)? rotation : controls::Action::Up);

                m_tiles[row][col].setOccupied(true);

            }else{
                continue;
            }

            m_obstacles.push_back(std::move(obstacle));
        }
    }
 }

Map::Map(const Point<float>& worldSize, const Point<float>& tileSize){
    initMap(worldSize, tileSize);

    for (unsigned short row = 0 ; row < m_rows; ++row) {
        for (unsigned short col = 0 ; col < m_columns; ++col) {
            m_tiles[row][col] = 
            Tile{Point<float>{static_cast<float>(col * tileSize.x),static_cast<float>(row * tileSize.y)},
                Point<float>(static_cast<float>(tileSize.x),static_cast<float>(tileSize.y))
            };
        }
    }
}

void Map::initMap(const Point<float>& worldSize, const Point<float>& tileSize) {
    m_worldSize = worldSize;
    m_rows = static_cast<unsigned short>(worldSize.y / tileSize.y) + 1 ;
    m_columns = static_cast<unsigned short>(worldSize.x / tileSize.x) + 1;
    
    if (!m_tileTexture.loadFromFile("../resources/textures/map/tiles.png")) {
        std::cerr << "Could not load the Tile textures in the Map\n";
    } 

    if (!m_obstacleTexture.loadFromFile("../resources/textures/map/obstacles.png")) {
        std::cerr << "Could not load the Obstacles textures in the Map\n";
    } 

    m_tileTexture.setSmooth(false);
    m_tileSprite.setTexture(m_tileTexture);

    m_obstacleTexture.setSmooth(true);
    m_obstacleSprite.setTexture(m_obstacleTexture);
    
    m_tiles.resize(m_rows);

    for (unsigned short row = 0 ; row < m_rows; ++row) {
       m_tiles[row].resize(m_columns);
    }
}

bool Map::hasAllKeys(const nlohmann::json& json, const std::vector<std::string>& keys) const{
    return std::all_of(keys.begin(), keys.end(), [&json](const std::string& key) {
        return json.contains(key);
    });
}

// Getters
std::vector<Obstacle>& Map::getObstacles(){
    return m_obstacles;
}
const std::vector<Obstacle>& Map::getObstacles() const{
    return m_obstacles;
}

std::vector<std::vector<Tile>>& Map::getTiles(){
    return m_tiles;
}

const std::vector<std::vector<Tile>>& Map::getTiles() const{
    return m_tiles;
}
Point<float> Map::getWorldSize() const{
    return m_worldSize;
}

// Actions
void Map::draw(Painter& painter) const {
    for (const auto& tiles: m_tiles) {
        for (const auto& tile: tiles) {
            painter.draw(tile, tile.getType(), tile.getRotation() ,m_tileSprite);
        }
    }

    for (const auto& obstacle: m_obstacles) {
       painter.draw(obstacle, obstacle.getType(), obstacle.getRotation() , m_obstacleSprite);
    }
}