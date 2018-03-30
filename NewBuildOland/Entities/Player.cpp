#include "stdafx.h"
#include "Player.h"
#include "../States/StateGame.h"
#include "../Utils/Animation.h"
#include "../Events/EventManager.h"
#include "../Events/PlaceableEnterEvent.h"
#include "../Events/PlaceableLeaveEvent.h"

Player::Player(World &world)
	: PhysicEntity()
{
	currentWorld = &world;
	setSize(sf::Vector2f(80, 80));
	setFillColor(sf::Color::White);
	setOrigin(getSize().x / 2, getSize().y / 2);
	setOnMapColor(sf::Color(0, 255, 0));
	setPosition(sf::Vector2f((float)world.getInitialPlayerPos().x * StateGame::TILE_SIZE, (float)world.getInitialPlayerPos().y * StateGame::TILE_SIZE));
	Texture* t = new Texture();
	(*t).loadFromFile("Res/characters.png");
	setTexture(t);

	hitboxWidth = 0.75f;
	hitboxHeightBottom = -0.8;
	hitboxHeightTop = 1.1;

	anima = Animation();
	anima.setInterval(0.12);

	std::vector<sf::IntRect> idleAnim = std::vector<sf::IntRect>();
	idleAnim.push_back(sf::IntRect(37, 9, 32, 32));
	anima.addAnimation(idleAnim);

	std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();
	//Walking to north
	walkingAnim.push_back(sf::IntRect(5, 105, 32, 32));
	walkingAnim.push_back(sf::IntRect(37, 105, 32, 32));
	walkingAnim.push_back(sf::IntRect(69, 105, 32, 32));
	walkingAnim.push_back(sf::IntRect(37, 105, 32, 32));
	anima.addAnimation(walkingAnim);
	//Walking to south
	walkingAnim = std::vector<sf::IntRect>();
	walkingAnim.push_back(sf::IntRect(5, 9, 32, 32));
	walkingAnim.push_back(sf::IntRect(37, 9, 32, 32));
	walkingAnim.push_back(sf::IntRect(69, 9, 32, 32));
	walkingAnim.push_back(sf::IntRect(37, 9, 32, 32));
	anima.addAnimation(walkingAnim);
	//Walking to east
	walkingAnim = std::vector<sf::IntRect>();
	walkingAnim.push_back(sf::IntRect(5, 73, 32, 32));
	walkingAnim.push_back(sf::IntRect(37, 73, 32, 32));
	walkingAnim.push_back(sf::IntRect(69, 73, 32, 32));
	walkingAnim.push_back(sf::IntRect(37, 73, 32, 32));
	anima.addAnimation(walkingAnim);
	//Walking to west
	walkingAnim = std::vector<sf::IntRect>();
	walkingAnim.push_back(sf::IntRect(5, 41, 32, 32));
	walkingAnim.push_back(sf::IntRect(37, 41, 32, 32));
	walkingAnim.push_back(sf::IntRect(69, 41, 32, 32));
	walkingAnim.push_back(sf::IntRect(37, 41, 32, 32));
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
	//The movement byte is used as a flag to choose the right animation
	char movement = 0;
	//Movement code
	sf::Vector2f oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		setPosition(sf::Vector2f(oldpos.x - SPEED * delta, oldpos.y));
		movement += 8;
	}
	if (touchesBlock())
		setPosition(oldpos);
	oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		setPosition(sf::Vector2f(oldpos.x + SPEED * delta, oldpos.y));
		movement += 4;
	}
	if (touchesBlock())
		setPosition(oldpos);
	oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		setPosition(sf::Vector2f(oldpos.x, oldpos.y - SPEED * delta));
		movement += 1;
	}
	if (touchesBlock())
		setPosition(oldpos);
	oldpos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		setPosition(sf::Vector2f(oldpos.x, oldpos.y + SPEED * delta));
		movement += 2;
	}
	if (touchesBlock())
		setPosition(oldpos);
	//Choice of animation
	switch (movement)
	{
	case 1:
		anima.selectAnimation(1);
		break;
	case 2:
		anima.selectAnimation(2);
		break;
	case 4:
		anima.selectAnimation(3);
		break;
	case 8:
		anima.selectAnimation(4);
		break;
	case 9:
		anima.selectAnimation(4);
		break;
	case 10:
		anima.selectAnimation(4);
		break;
	case 5:
		anima.selectAnimation(3);
		break;
	case 6:
		anima.selectAnimation(3);
		break;
	default:
		anima.selectAnimation(0);
		break;
	}
	setTextureRect(anima.getRect());

	//Block enter and leave event
	sf::Vector2i blockOn = sf::Vector2i(roundf(getPosition().x / StateGame::TILE_SIZE), roundf(getPosition().y / StateGame::TILE_SIZE));
	sf::Vector2u uBlockOn = sf::Vector2u(blockOn.x, blockOn.y);
	if (lastPos != uBlockOn)
	{	
		unsigned short id = currentWorld->getBlockId(blockOn.x, blockOn.y);
		EventManager::OnPlaceableLeave(PlaceableLeaveEvent(lastPos, this, id, currentWorld->getStateGame()));
		if (blockOn.x >= 0 && blockOn.y >= 0 && blockOn.x < currentWorld->getWorldSize().x && blockOn.y < currentWorld->getWorldSize().y)
			EventManager::OnPlaceableEnter(PlaceableEnterEvent(lastPos, this, id, currentWorld->getStateGame()));
		lastPos = uBlockOn;
	}
}
