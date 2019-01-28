#include "ItemStack.h"
#include "Inventory.h"
#include "../Placeables/ItemAir.h"
#include "ItemSet.h"

#include <cassert>

ItemSet* ItemStack::currentItemSet;

ItemStack::ItemStack()
{
    id = 0;
    quantity = 0;
}

ItemStack::ItemStack(Item* item, unsigned short count)
{
    /*
    //If it has a nullptr it's the same as an ItemStack() with a quantity
    if(item == nullptr) {
        ItemStack::item = ItemSet::getSomeAir();
        ItemStack::quantity = quantity;
        return;
    }
    */
    id = item->getItemId();
    quantity = count;
}

Item* ItemStack::getItem() const
    { return currentItemSet->getItemById(id); }

void ItemStack::remove(unsigned short count)
{
    assert(count <= quantity);

    quantity -= count;

    if (quantity == 0)
        id = 0;
}

bool ItemStack::stack(ItemStack otherStack)
{
    if (otherStack.getID() == id)
    {
        quantity += otherStack.getQuantity();
        return true;
    }
    else
        return false;
}
