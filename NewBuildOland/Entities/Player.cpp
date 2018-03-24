#include "stdafx.h"
#include "Player.h"
#include "../States/StateGame.h"
#include "../Utils/Animation.h"

Player::Player(World &world)
	: PhysicEntity()
{
	currentWorld = &world;
	setSize(sf::Vector2f(60, 60));
	setFillColor(sf::Color::White);
	//setOutlineColor(sf::Color::White);
	//setOutlineThickness(8);
	setOrigin(30, 30);
	setOnMapColor(sf::Color(0, 255, 0));
	setPosition(sf::Vector2f((float)world.getInitialPlayerPos().x * StateGame::TILE_SIZE, (float)world.getInitialPlayerPos().y * StateGame::TILE_SIZE));
	Texture* t = new Texture();
	(*t).loadFromFile("Res/player_sheet.png");
	setTexture(t);

	anima = Animation();
	std::vector<sf::IntRect> idleAnim = std::vector<sf::IntRect>();
	idleAnim.push_back(sf::IntRect(0, 0, 2, 2));
	idleAnim.push_back(sf::IntRect(2, 0, 2, 2));
	std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();
	walkingAnim.push_back(sf::IntRect(0, 2, 2, 2));
	walkingAnim.push_back(sf::IntRect(2, 2, 2, 2));
	anima.addAnimation(idleAnim);
	anima.addAnimation(walkingAnim);

	setTextureRect(anima.getRect());
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
	bool moving = false;
	sf::Vector2f oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		setPosition(sf::Vector2f(oldpos.x - SPEED * delta, oldpos.y));
		moving = true;
	}
	if (touchesBlock())
		setPosition(oldpos);
	oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		setPosition(sf::Vector2f(oldpos.x + SPEED * delta, oldpos.y));
		moving = true;
	}
	if (touchesBlock())
		setPosition(oldpos);
	oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		setPosition(sf::Vector2f(oldpos.x, oldpos.y - SPEED * delta));
		moving = true;
	}
	if (touchesBlock())
		setPosition(oldpos);
	oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moving = true;
		setPosition(sf::Vector2f(oldpos.x, oldpos.y + SPEED * delta));
	}
	if (touchesBlock())
		setPosition(oldpos);
	if (moving)
	{
		anima.selectAnimation(1);
	}
	else
	{
		anima.selectAnimation(0);
	}
	setTextureRect(anima.getRect());
}
