#pragma once
#include "Entities.h"
#include "PhysicEntity.h"

class Player : public PhysicEntity
{
public:
	Player(World &world);
	Player();
	~Player();
	void update(double delta) override;
};

