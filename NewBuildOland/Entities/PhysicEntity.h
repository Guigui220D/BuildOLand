#pragma once
#include "Entities.h"

class PhysicEntity : public Entities
{
public:
	PhysicEntity(World *world = nullptr);
	~PhysicEntity();
	virtual void update(double delta) override;
	int touchesBlock();
};

