#pragma once
#include "SFML/Audio.hpp"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

