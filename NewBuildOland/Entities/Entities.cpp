#include "stdafx.h"
#include "Entities.h"


Entities::Entities()
{
}


Entities::~Entities()
{
}

void Entities::update(double delta)
{
}

sf::Vector2f Entities::getVelocity()
{
	return velocity;
}

void Entities::setVelocity(sf::Vector2f newVel)
{
	velocity = newVel;
}
