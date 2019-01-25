#include "ItemSet.h"

ItemSet::ItemSet()
{
    //ctor
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
