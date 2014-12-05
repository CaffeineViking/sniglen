#include "Assets.hpp"

const sf::Texture& Assets::LOAD_TEXTURE(const std::string& name) {
    if (TEXTURES_.find(name) == TEXTURES_.end()) {
        TEXTURES_[name].loadFromFile(IMAGES_PATH + name);
    }

    return TEXTURES_[name];
}

const sf::SoundBuffer& Assets::LOAD_SOUND(const std::string& name) {
    if (SOUNDS_.find(name) == SOUNDS_.end()) {
        SOUNDS_[name].loadFromFile(AUDIO_PATH + name);
    }

    return SOUNDS_[name];
}

sf::Music& Assets::LOAD_MUSIC(const std::string& name) {
    if (MUSIC_.find(name) == MUSIC_.end()) {
        MUSIC_[name].openFromFile(AUDIO_PATH + name);
    }

    return MUSIC_[name];
}

const sf::Font& Assets::LOAD_FONT(const std::string& name){
    if(FONTS_.find(name) == FONTS_.end()){
        FONTS_[name].loadFromFile(OTHERS_PATH + name);
    }

    return FONTS_[name];
}

const std::string Assets::PATH{"share/"};
const std::string Assets::AUDIO_PATH{PATH + "audio/"};
const std::string Assets::IMAGES_PATH{PATH + "images/"};
const std::string Assets::OTHERS_PATH{PATH + "others/"};

const sf::Vector2f Assets::WINDOW_SIZE{1280, 720};
std::unordered_map<std::string, sf::Texture> Assets::TEXTURES_;
std::unordered_map<std::string, sf::SoundBuffer> Assets::SOUNDS_;
std::unordered_map<std::string, sf::Music> Assets::MUSIC_;
std::unordered_map<std::string, sf::Font> Assets::FONTS_;
