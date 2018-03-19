#pragma once
#include "Entities.h"

class PhysicEntity : public Entities
{
public:
	PhysicEntity();
	~PhysicEntity();
	virtual void update(double delta) override;
	int touchesBlock();
};

