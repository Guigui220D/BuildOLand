#include "Animation.h"


Animation::Animation()
{
	animClk = sf::Clock();
	interval = 0.25;
	selectedAnim = 0;
	animations = std::vector<std::vector<sf::IntRect>>();
}


Animation::~Animation()
{
}

sf::IntRect Animation::getRect()
{
	int animLenght = animations[selectedAnim].size();
	int at = (int)(animClk.getElapsedTime().asSeconds() / interval);
	at %= animLenght;
	return animations[selectedAnim][at];
}

void Animation::setInterval(float t)
{
	if (t > 0)
		interval = t;
}

float Animation::getInterval()
{
	return interval;
}

bool Animation::selectAnimation(unsigned int anim)
{
	if (anim == selectedAnim)
		return false;
	resetClock();
	if (anim >= animations.size())
	{
		return false;
	}
	else
	{
		selectedAnim = anim;
		return true;
	}
}

unsigned int Animation::getSelectedAnim()
{
	return selectedAnim;
}

void Animation::resetClock()
{
	animClk.restart();
}

void Animation::addAnimation(std::vector<sf::IntRect> anim)
{
	animations.push_back(anim);
}
