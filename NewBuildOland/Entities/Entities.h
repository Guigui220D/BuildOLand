#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"

class Entities : public sf::RectangleShape
{
public:
	Entities();
	~Entities();
	void update(double delta);
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f newVel);
protected:
	sf::Vector2f velocity;
};

