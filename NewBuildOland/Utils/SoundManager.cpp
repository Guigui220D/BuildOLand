#include "stdafx.h"
#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
}

sf::Sound* SoundManager::addSound(std::string soundName) {
	sf::SoundBuffer* newSoundBuffer = new sf::SoundBuffer();
	//Load the sound from the buffer
	if (!newSoundBuffer->loadFromFile(REPERTORY_NAME + soundName)) {
		std::cout << "Error: failed loading sound " << REPERTORY_NAME << soundName << std::endl;
	}

	//Create the Sound and add it to the array
	sf::Sound* newSound = new sf::Sound();
	newSound->setBuffer(*newSoundBuffer);
	sounds.push_back(newSound);
	soundNames.push_back(soundName);
	return newSound;
}

sf::Sound* SoundManager::getSound(std::string soundName)
{
	//Find the sound and return it
	for(unsigned i = 0; i < soundNames.size(); i++) {
		if(soundNames[i] == soundName) {
			return sounds[i];
		}
	}
	//Sound doesn't exist : init the sound
	return addSound(soundName);
}

sf::Music* SoundManager::addMusic(std::string musicName)
{
	//Init music
	sf::Music* music = new sf::Music();
	if(!music->openFromFile(REPERTORY_NAME + musicName)) {
		std::cout << "Error: failed loading music " << REPERTORY_NAME << musicName << std::endl;
	}
	//Save the music in the arrays
	musics.push_back(music);
	musicNames.push_back(musicName);

	//And finally return the music initialized
	return music;
}

sf::Music* SoundManager::getMusic(std::string musicName)
{
	//Find the msuic and return it
	for (unsigned i = 0; i < musicNames.size(); i++) {
		if (musicNames[i] == musicName) {
			return musics[i];
		}
	}
	//Music doesn't exist : init the sound
	return addMusic(musicName);
}




SoundManager::~SoundManager()
{
	//Delete each Sound
	for (unsigned i = 0; i < soundNames.size(); i++) {
		delete sounds[i];	
	}
}
