#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	setSize(sf::Vector2f(60, 60));
	setFillColor(sf::Color(127, 0, 0));
	setOutlineColor(sf::Color::White);
	setOutlineThickness(8);
	setOrigin(30, 30);
	setOnMapColor(sf::Color(0, 255, 0));
}


Player::~Player()
{
}

void Player::update(double delta)
{
	if (!touchesBlock())
		setPosition(getPosition().x + delta * 50, getPosition().y + delta * 20);
}
