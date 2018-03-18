#include "stdafx.h"
#include "PhysicEntity.h"
#include "iostream"

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
	int x = getPosition().x / 80;
	int y = getPosition().y / 80;
	int nx;
	int ny;
	for (int xx = -1; xx <= 1; xx++)
	{
		nx = (x + xx);
		for (int yy = -1; yy <= 1; yy++)
		{
			ny = (y + yy);		
			if (currentWorld->getBlockId(sf::Vector2u(nx, ny)) != 0)
			{
				sf::Vector2f ppos = getPosition();
				sf::Vector2f psize = getSize();
				if (ppos.x + psize.x / 2 > nx * 80 - 40 && ppos.y + psize.y / 2 > ny * 80 - 40 && ppos.x - psize.x / 2 < nx * 80 + 40 && ppos.y - psize.y / 2 < ny * 80 + 40)
					return 1;
			}
		}
	}
	return 0;
}
