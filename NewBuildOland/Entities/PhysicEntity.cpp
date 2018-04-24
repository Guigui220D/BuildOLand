#include "PhysicEntity.h"
#include "iostream"
#include "../States/StateGame.h"

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
			if (currentWorld->getBlockAt(nx, ny)->hasHitbox())
			{
				if (currentWorld->getBlockAt(nx, ny)->hasVolume())
				{

					sf::Vector2f ppos = getPosition();
					sf::Vector2f psize = getSize();
					if (ppos.x + (psize.x * 0.5f) * hitboxWidth > nx * StateGame::TILE_SIZE - StateGame::TILE_SIZE * 0.5f
						&& ppos.y + (psize.y * 0.5f) * hitboxHeightBottom > ny * StateGame::TILE_SIZE - StateGame::TILE_SIZE * 0.5f - 0.5f * StateGame::TILE_SIZE
						&& ppos.x - (psize.x * 0.5f) * hitboxWidth < nx * StateGame::TILE_SIZE + StateGame::TILE_SIZE * 0.5f
						&& ppos.y - (psize.y * 0.5f) * hitboxHeightTop < ny * StateGame::TILE_SIZE + StateGame::TILE_SIZE * 0.5f - 0.5f * StateGame::TILE_SIZE)
						return 1;
				}
				else
				{
					sf::Vector2f ppos = getPosition();
					sf::Vector2f psize = getSize();
					if (ppos.x + (psize.x * 0.5f) * hitboxWidth > nx * StateGame::TILE_SIZE - StateGame::TILE_SIZE * 0.5f
						&& ppos.y + (psize.y * 0.5f) * hitboxHeightBottom > ny * StateGame::TILE_SIZE - StateGame::TILE_SIZE * 0.5f
						&& ppos.x - (psize.x * 0.5f) * hitboxWidth < nx * StateGame::TILE_SIZE + StateGame::TILE_SIZE * 0.5f
						&& ppos.y - (psize.y * 0.5f) * hitboxHeightTop < ny * StateGame::TILE_SIZE + StateGame::TILE_SIZE * 0.5f)
						return 1;
				}
			}
		}
	}
	return 0;
}
