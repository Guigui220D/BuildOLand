#pragma once
#include <SFML\system.hpp>
#include <SFML\graphics.hpp>

class Animation
{
public:
	Animation();
	~Animation();
	sf::IntRect getRect();
	void setInterval(float t);
	float getInterval();
	bool selectAnimation(unsigned int anim);
	unsigned int getSelectedAnim();
	void resetClock();
	void addAnimation(std::vector<sf::IntRect> anim);
protected:
	sf::Clock animClk;
	float interval;
	unsigned int selectedAnim;
	std::vector<std::vector<sf::IntRect>> animations;
};

