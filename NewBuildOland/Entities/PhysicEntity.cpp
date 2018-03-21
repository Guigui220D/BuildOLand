#include "stdafx.h"
#include "PhysicEntity.h"
#include "iostream"
#include "../States/StateGame.h"

PhysicEntity::PhysicEntity()
	: Entities()
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
	int x = (int)(getPosition().x / StateGame::TILE_SIZE);
	int y = (int)(getPosition().y / StateGame::TILE_SIZE);
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
				if (ppos.x + psize.x / 2 > nx * StateGame::TILE_SIZE - StateGame::TILE_SIZE / 2.0f && ppos.y + psize.y / 2 > ny * StateGame::TILE_SIZE - StateGame::TILE_SIZE / 2.0f && ppos.x - psize.x / 2 < nx * StateGame::TILE_SIZE - StateGame::TILE_SIZE / 2.0f && ppos.y - psize.y / 2 < ny * StateGame::TILE_SIZE - StateGame::TILE_SIZE / 2.0f)
					return 1;
			}
		}
	}
	return 0;
}
