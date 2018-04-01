#pragma once
#include "SFML/Audio.hpp"
#include <Vector>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	sf::Sound* getSound(std::string soundName);
	sf::Music* getMusic(std::string musicName);

private:
	std::string const REPERTORY_NAME = "Res/sound/";

	std::vector<sf::Sound*> sounds;
	std::vector<std::string> soundNames;
	std::vector<sf::Music*> musics;
	std::vector<std::string> musicNames;


	sf::Sound* addSound(std::string soundName);
	sf::Music* addMusic(std::string musicName);
};