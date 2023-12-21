#include "CacheManager.h"
#include <filesystem> 
#include <iostream>

std::unordered_map<std::string, sf::Texture> CacheManager::textureCache;
std::unordered_map<std::string, sf::Texture> CacheManager::textureCacheHD;
std::unordered_map<std::string, sf::Font> CacheManager::fontCache;

const sf::Texture& CacheManager::getTexture(const std::string& filePath, bool textureHD) {
    auto it = textureCacheHD.find(filePath);
    
    if (it != textureCacheHD.end()) {
        return (textureHD)? it->second :textureCache[filePath];
    } else{
        sf::Texture texture;
        if (texture.loadFromFile(filePath)) {
            textureCache[filePath] = texture;
            texture.setSmooth(true);
            textureCacheHD[filePath] = texture;
            return (textureHD)? textureCacheHD[filePath] :textureCache[filePath];
        } else {
            std::cerr << "Could not load the texture: " << filePath << std::endl;
            return textureCache[""];
        }
    }
}

const sf::Font& CacheManager::getFont(const std::string& filePath){
    auto it = fontCache.find(filePath);
    if (it != fontCache.end()) {
        return it->second;
    } else {
        sf::Font font;
        if (font.loadFromFile(filePath)) {
            fontCache[filePath] = font;
            return fontCache[filePath];
        } else {
            std::cerr << "Could not load the font: " << filePath << std::endl;
            return fontCache[""];
        }
    }
}

void CacheManager::loadTexturesFrom(const std::string& folderPath) {
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        const std::string& filePath = entry.path().string();
        // Check if the file is a regular file (not a directory, symbolic link, etc.)
        if (std::filesystem::is_regular_file(entry.status())) {
            getTexture(filePath);
        }
    }
}