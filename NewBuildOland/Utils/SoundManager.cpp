#include "stdafx.h"
#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
	if (!buffer.loadFromFile("Res/sound/forest-ambiance.ogg")) {
		std::cout << "FAILED LOADING SOUND" << std::endl;
	}

	sound.setBuffer(buffer);
	sound.play();
	sound.setVolume(10);
	sound.setLoop(true);
}


SoundManager::~SoundManager()
{
}
