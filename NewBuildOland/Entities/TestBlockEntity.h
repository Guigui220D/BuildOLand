#pragma once
#include "BlockEntity.h"

class TestBlockEntity : public BlockEntity
{
public:
	TestBlockEntity(World* world, sf::Vector2u tile);
	~TestBlockEntity();
	void OnInteract() override;
};

