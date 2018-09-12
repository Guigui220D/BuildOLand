#include "PhysicEntity.h"
#include "iostream"
#include "../States/StateGame.h"
#include "math.h"

PhysicEntity::PhysicEntity(World *world, unsigned id)
	: Entities(world, id)
{
}


PhysicEntity::~PhysicEntity()
{
}

void PhysicEntity::update(float delta)
{
}

int PhysicEntity::touchesBlock()
{
    if (abs(getWorldPos().x - game->getPlayer()->getWorldPos().x) >= 54 || abs(getWorldPos().y - currentWorld->getStateGame()->getPlayer()->getWorldPos().y) >= 54)
        return 0;
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
			if (currentWorld->getBlockAt(sf::Vector2i(nx, ny), false)->hasHitbox())
			{
				if (currentWorld->getBlockAt(sf::Vector2i(nx, ny), false)->hasVolume())
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
