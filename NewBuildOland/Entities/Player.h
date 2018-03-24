#pragma once
#include "Entities.h"
#include "PhysicEntity.h"
#include "../Utils/Animation.h"

class Player : public PhysicEntity
{
public:
	Player(World &world);
	Player();
	~Player();
	void update(double delta) override;
private:
	Animation anima;
	static const int SPEED = 300;
};

