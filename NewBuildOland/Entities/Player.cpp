#include "stdafx.h"
#include "Player.h"
#include "../States/StateGame.h"

Player::Player(World &world)
	: PhysicEntity()
{
	currentWorld = &world;
	setSize(sf::Vector2f(60, 60));
	setFillColor(sf::Color(127, 0, 0));
	//setOutlineColor(sf::Color::White);
	//setOutlineThickness(8);
	setOrigin(30, 30);
	setOnMapColor(sf::Color(0, 255, 0));
	setPosition(sf::Vector2f((float)world.getInitialPlayerPos().x * StateGame::TILE_SIZE, (float)world.getInitialPlayerPos().y * StateGame::TILE_SIZE));
}

Player::Player() 
	: PhysicEntity()
{
	setSize(sf::Vector2f(60, 60));
	setFillColor(sf::Color(127, 0, 0));
	//setOutlineColor(sf::Color::White);
	//setOutlineThickness(8);
	setOrigin(30, 30);
	setOnMapColor(sf::Color(0, 255, 0));
}

Player::~Player()
{
}

void Player::update(double delta)
{
	sf::Vector2f oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		setPosition(sf::Vector2f(oldpos.x - SPEED * delta, oldpos.y));
	}
	if (touchesBlock())
		setPosition(oldpos);
	oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		setPosition(sf::Vector2f(oldpos.x + SPEED * delta, oldpos.y));
	}
	if (touchesBlock())
		setPosition(oldpos);
	oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		setPosition(sf::Vector2f(oldpos.x, oldpos.y - SPEED * delta));
	}
	if (touchesBlock())
		setPosition(oldpos);
	oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		setPosition(sf::Vector2f(oldpos.x, oldpos.y + SPEED * delta));
	}
	if (touchesBlock())
		setPosition(oldpos);
}
