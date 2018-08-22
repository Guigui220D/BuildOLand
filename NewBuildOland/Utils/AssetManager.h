#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <iostream>

class AssetManager
{
    public:
        AssetManager();
        ~AssetManager();

        static const std::string AUDIO_REPERTORY_NAME;
        static const std::string FONT_REPERTORY_NAME;
        static const std::string TEXTURE_REPERTORY_NAME;

        void addMusic(sf::Music* music, const std::string name);
        void addSound(sf::SoundBuffer* sound, const std::string name);
        void addTexture(sf::Texture* texture, const std::string name);
        void addFont(sf::Font* font, const std::string name);

        bool loadMusicFromFile(const std::string path, const std::string name);
        bool loadSoundFromFile(const std::string path, const std::string name);
        bool loadTextureFromFile(const std::string path, const std::string name);
        bool loadFontFromFile(const std::string path, const std::string name);

        sf::Music* getMusic(const std::string name);
        sf::SoundBuffer* getSound(const std::string name);
        sf::Texture* getTexture(const std::string name);
        sf::Font* getFont(const std::string name);

        inline sf::Texture* getErrorTexture() { return &errorTexture; };

    private:
        std::unordered_map<std::string, sf::Music*> musics;
        std::unordered_map<std::string, sf::SoundBuffer*> sounds;
        std::unordered_map<std::string, sf::Texture*> textures;
        std::unordered_map<std::string, sf::Font*> fonts;

        sf::Texture errorTexture;
};
