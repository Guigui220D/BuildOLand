#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	setSize(sf::Vector2f(100, 100));
	setFillColor(sf::Color(127, 0, 0));
	setOutlineColor(sf::Color::White);
	setOutlineThickness(8);
}


Player::~Player()
{
}

void Player::update(double delta)
{
	setPosition(getPosition().x + delta * 100, getPosition().y);
}
