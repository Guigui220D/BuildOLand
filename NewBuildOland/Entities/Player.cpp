#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	setSize(sf::Vector2f(100, 100));
	setFillColor(sf::Color(127, 0, 0));
	setOutlineColor(sf::Color::White);
	setOutlineThickness(8);
	setOrigin(50, 50);
	setOnMapColor(sf::Color(255, 64, 32));
}


Player::~Player()
{
}

void Player::update(double delta)
{
	if (!touchesBlock())
		setPosition(getPosition().x + delta * 50, getPosition().y + delta * 20);
}
