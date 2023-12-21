#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

// Utility class for managing textures
class CacheManager {
public:
    static const sf::Texture& getTexture(const std::string& filePath, bool textureHD = true);
    static const sf::Font& getFont(const std::string& filePath);
    static void loadTexturesFrom(const std::string& folderPath);

private:
    CacheManager() {}

private:
    // Cache to store loaded textures.
    static std::unordered_map<std::string, sf::Texture> textureCache;
    static std::unordered_map<std::string, sf::Texture> textureCacheHD;
    // Cache to store loaded fonts.
    static std::unordered_map<std::string, sf::Font> fontCache;
};
