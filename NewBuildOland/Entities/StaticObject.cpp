#include "StaticObject.h"


StaticObject::StaticObject(World *world)
	: Entities(world)
{
	setOnMapColor(sf::Color::Transparent);
	setOnMapRadius(0);
}


StaticObject::~StaticObject()
{
}
