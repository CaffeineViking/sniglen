#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <string>
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

class Assets {
public:
    static const sf::Texture& LOAD_TEXTURE(const std::string&);
    static const sf::SoundBuffer& LOAD_SOUND(const std::string&);
    static sf::Music& LOAD_MUSIC(const std::string&);
    static const sf::Font& LOAD_FONT(const std::string&);
    static const sf::Vector2f WINDOW_SIZE;

private:
    static const std::string PATH;
    static const std::string AUDIO_PATH;
    static const std::string IMAGES_PATH;
    static const std::string OTHERS_PATH;

    static std::unordered_map<std::string, sf::Texture> TEXTURES_;
    static std::unordered_map<std::string, sf::SoundBuffer> SOUNDS_;
    static std::unordered_map<std::string, sf::Music> MUSIC_;
    static std::unordered_map<std::string, sf::Font> FONTS_;
};

#endif
