#pragma once
#include "Entities.h"
#include "../States/StateGame.h"

class BlockEntity : public Entities
{
public:
	BlockEntity(World* world, sf::Vector2u tile, unsigned short blockId);
	~BlockEntity();
	virtual void OnInteract();
protected:
	sf::Vector2u blockPosition;
	unsigned short id;
};

