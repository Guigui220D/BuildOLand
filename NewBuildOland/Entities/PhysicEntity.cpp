#include "stdafx.h"
#include "PhysicEntity.h"


PhysicEntity::PhysicEntity(World *world)
	: Entities(world)
{
}


PhysicEntity::~PhysicEntity()
{
}

void PhysicEntity::update(double delta)
{
}

int PhysicEntity::touchesBlock()
{
	//Checks near blocks to entity
	int x = getPosition().x;
	int y = getPosition().y;
	int nx;
	int ny;
	for (int xx = -1; xx <= 1; xx++)
	{
		nx = x + xx;
		if (nx < 0)
			continue;
		for (int yy = -1; yy <= 1; yy++)
		{
			ny = y + y;
			if (ny < 0)
				continue;
			//Todo : add a way tochek if near block touches the entity
		}
	}
	return 0;
}
