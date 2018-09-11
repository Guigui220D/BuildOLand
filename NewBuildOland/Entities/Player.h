#pragma once
//#include "Entities.h"
//#include "PhysicEntity.h"
//#include "../Utils/Animation.h"
//#include "../Utils/Inventory.h"
#include "LivingEntity.h"

class Player : public LivingEntity
{
public:
	Player(World *world, sf::String displayName, unsigned int id);
	~Player();
	void drawMore(sf::RenderWindow& window) override;

	inline void setCurrentWorld(World* newWorld) { currentWorld = newWorld; };

	inline sf::String getDisplayName() { return nameText.getString(); };

	std::vector<unsigned char> getBytes() override;

private:
	sf::Vector2i lastPos;

	void initInventory(World* currentWorld);

protected:
	std::string getTextureName() override;
	std::vector<IntRect> getIdleAnim() override;
	std::vector<IntRect> getNorthWalkAnim() override;
	std::vector<IntRect> getSouthWalkAnim() override;
	std::vector<IntRect> getEastWalkAnim() override;
	std::vector<IntRect> getWestWalkAnim() override;

	void updateMovement(float dt) override;

	sf::Text nameText; //Display name

	//Used to send data to server
	unsigned char keysState = 0;
};

