#include "StaticObject.h"


StaticObject::StaticObject(World *world, unsigned id)
	: Entities(world, id)
{
	setOnMapColor(sf::Color::Transparent);
	setOnMapRadius(0);
}


StaticObject::~StaticObject()
{
}
