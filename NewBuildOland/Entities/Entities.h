#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "../Worlds/World.h"

#include "EntityCodes.h"

class Entities : public sf::RectangleShape
{
public:
	Entities(World *world, unsigned int id);
	~Entities();
	virtual void update(float delta);

	sf::CircleShape* getOnMap();
	inline void setOnMapColor(sf::Color color) { onMap.setFillColor(color); };
	void setOnMapRadius(float radius) { onMap.setRadius(radius); };
	virtual void drawMore(sf::RenderWindow& window);

	sf::Vector2f getWorldPos();

	inline World *getCurrentWorld() const { return currentWorld; };

	bool mustBeRemoved = false;

	inline unsigned int getID() const { return id; };
	inline virtual EntityCodes getCode() const { return EntityCodes::base; }

	//To take a packet containing some info about the entity
	inline virtual void takePacket(sf::Packet p) {};
	//To take some data from a savefile
	void takeData(unsigned char*& dataPtr);
	inline size_t getDataSize() const { return dataSize; };

	//Do not forget to delete what is returned
    virtual unsigned char* getData() const;

protected:
	World *currentWorld = nullptr;
	StateGame *game = nullptr;

	//Determines the amount of data that should be taken with takeData
    size_t dataSize;
    inline void setDataSize(size_t size) { dataSize = size; };

private:
	sf::CircleShape onMap;

	unsigned int id;

};

