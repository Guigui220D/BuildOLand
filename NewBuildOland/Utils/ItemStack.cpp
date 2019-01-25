#include "ItemStack.h"
#include "Inventory.h"
#include "../Placeables/ItemAir.h"
#include "ItemSet.h"

ItemStack::ItemStack() {
    item = ItemSet::getSomeAir();
    ItemStack::quantity = 0;
}

ItemStack::ItemStack(Item* item) {

    //If it has a nullptr it's the same as an ItemStack() without arguments
    if(item == nullptr) {
        ItemStack::item = ItemSet::getSomeAir();
        ItemStack::quantity = 0;
        return;
    }

    ItemStack::item = item;
    ItemStack::quantity = 1;
}

ItemStack::ItemStack(Item* item, unsigned short quantity) {
    //If it has a nullptr it's the same as an ItemStack() with a quantity
    if(item == nullptr) {
        ItemStack::item = ItemSet::getSomeAir();
        ItemStack::quantity = quantity;
        return;
    }

    ItemStack::item = item;
    ItemStack::quantity = quantity;
}

unsigned short ItemStack::getQuantity() const {
    return quantity;
}

Item* ItemStack::getItem() const {
    return item;
}

bool ItemStack::isEmpty() {
    return quantity <= 0;
}

void ItemStack::add(unsigned int quantity) {
    ItemStack::quantity += quantity;
}

void ItemStack::remove(unsigned int quantity) {
    ItemStack::quantity -= quantity;

    if(quantity <= 0) {
        ItemStack::quantity = 0;
        item = ItemSet::getSomeAir();
    }
}

bool ItemStack::stack(ItemStack otherStack)
{
    if (otherStack.item == item)
    {
        quantity += otherStack.getQuantity();
        return true;
    }
    else
        return false;
}
