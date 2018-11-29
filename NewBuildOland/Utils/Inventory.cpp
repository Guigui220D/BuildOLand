#include "Inventory.h"

Inventory::Inventory(unsigned short size) :
    size(size)
{
    inventory = new ItemStack[size];
}

Inventory::~Inventory()
{
    delete[] inventory;
}

bool Inventory::addItem(ItemStack itemStack)
{
    //First search if there is anything you can stack
    for(unsigned short i = 0; i < size; i++)
        if(inventory[i].stack(itemStack))
            return true;

    //Otherwise search for air
    for(unsigned short i = 0; i < size; i++) {
        if(inventory[i].getItem()->getName() == "AIR") {
            inventory[i] = itemStack;
            printf("test\n");
            return true;
        }
    }

    return false;
}

unsigned short Inventory::getSize() const {
    return size;
}

void Inventory::clearInventory() {
    ItemStack emptyItemStack;

    for(int i = 0; i < size; i++) {
        inventory[i] = emptyItemStack;
    }
}

ItemStack& Inventory::getItem(unsigned short pos) {
    return inventory[pos];
}
