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
	sf::Vector2f oldpos = getPosition();
	sf::Vector2f newpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		newpos += sf::Vector2f(-300 * delta, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		newpos += sf::Vector2f(300 * delta, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		newpos += sf::Vector2f(0, -300 * delta);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		newpos += sf::Vector2f(0, 300 * delta);
	}
	setPosition(newpos);
	if (touchesBlock())
		setPosition(oldpos);
}
