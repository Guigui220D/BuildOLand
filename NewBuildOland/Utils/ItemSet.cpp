#include "ItemSet.h"

//Tiles
#include "../Placeables/EngineeringBlocks/BlockSaver.h"
#include "../Placeables/EngineeringBlocks/TNTBlock.h"
#include "../Placeables/Grounds/GroundGrass.h"
#include "../Placeables/Grounds/WornConcrete.h"
#include "../Placeables/BuildingBlocks/OpenDoorBlock.h"
#include "../Placeables/BuildingBlocks/ClosedDoorBlock.h"
#include "../Placeables/Prototypes/BlinkerBlock.h"

Item* ItemSet::air;

ItemSet::ItemSet()
{
    generateItems();
    air = getItemByName("AIR");
}

ItemSet::~ItemSet()
{
    //dtor
}

unsigned short ItemSet::getItemIdByName(const std::string name) const
{
    auto i = itemNames.find(name);
    return (i != itemNames.end()) ? (i->second) : 0;
}

bool ItemSet::iterateThroughItems(Item*& item)
{
    if (iterator >= items.size())
    {
        iterator = 0;
        return false;
    }
    item = items.at(iterator++);
    return true;
}

void ItemSet::addItem(Item* item)
{
    std::string name = item->getName();
    if (itemNames.find(name) == itemNames.end())
    {
        //Add the item
        items.push_back(item);
        unsigned short id = items.size() - 1;
        item->setItemId(id);
        //Add the name in the map
        itemNames.emplace(std::pair<std::string, unsigned short>(name, id));
    }
    else
        std::cerr << "An item with the name \"" << name << "\" already exists, could not add it.\n";
}

void ItemSet::generateItems()
{
    //Blocks
    addItem(new Block(tileRectById(1), "AIR",				sf::Color(90, 70, 50),	false, false));
	addItem(new Block(tileRectById(7), "LOG",				sf::Color(135, 90, 30),	true, true, tileRectById(12)));
	addItem(new Block(tileRectById(6), "BRICK",			    sf::Color(90, 90, 90),	true));
	addItem(new Block(tileRectById(5), "CONCRETE_BLOCK",			sf::Color(90, 90, 90),	true));
	addItem(new Block(tileRectById(15), "METAL",			sf::Color(200, 200, 200),true));
	addItem(new Block(tileRectById(16), "GOLD",			    sf::Color(255, 255, 200),true));
	addItem(new TNTBlock(tileRectById(17), tileRectById(18)));
    addItem(new ClosedDoorBlock(tileRectById(22), tileRectById(20)));
    addItem(new OpenDoorBlock(tileRectById(23), tileRectById(21)));
	addItem(new Block(tileRectById(8), "PRESSURE_PLATE",   sf::Color(135, 30, 30), false, false));
	addItem(new BlockSaver(tileRectById(10)));
	addItem(new BlinkerBlock(tileRectById(17), tileRectById(12)));
    //Grounds
	addItem(new GroundGrass(tileRectById(2)));
	addItem(new Ground(tileRectById(3), "SAND", sf::Color(215, 215, 60)));
	addItem(new Ground(tileRectById(4), "WATER", sf::Color(60, 90, 210)));
	addItem(new Ground(tileRectById(5), "CONCRETE", sf::Color(155, 155, 155)));
	addItem(new WornConcrete(tileRectById(19), "WORN_CONCRETE", sf::Color(135, 135, 135)));
}

