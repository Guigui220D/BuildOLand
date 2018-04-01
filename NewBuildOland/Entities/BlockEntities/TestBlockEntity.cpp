#include "stdafx.h"
#include "TestBlockEntity.h"
#include <iostream>

TestBlockEntity::TestBlockEntity(World* world, sf::Vector2u tile) : BlockEntity(world, tile, 6)
{

}

TestBlockEntity::~TestBlockEntity()
{
}

void TestBlockEntity::OnInteract()
{
	std::cout << "Entity block working" << std::endl;
}
