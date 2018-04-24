#pragma once
#include "Entities.h"
#include "PhysicEntity.h"
#include "../Utils/Animation.h"
#include "../Utils/Inventory.h"

class Player : public PhysicEntity
{
public:
	Player(World *world);
	Player();
	~Player();
	void update(double delta) override;

	Inventory* getInventory();

private:
	Animation anima;
	static const int SPEED = 300;
	sf::Vector2u lastPos;

	Inventory inventory;
	void initInventory(World *currentWorld);
};

