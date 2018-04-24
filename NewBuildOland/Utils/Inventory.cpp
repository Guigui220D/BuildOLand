#include "Inventory.h"

Inventory::Inventory(unsigned short size) {
    Inventory::size = size;
    for(unsigned short i = 0; i < size; i++) {
        inventory.push_back(ItemStack());
    }
}

void Inventory::setItem(unsigned short pos, ItemStack itemStack) {
    inventory[pos] = itemStack;
}

/**
 * Adds an item to the inventory
 * @param itemStack
 * @return false if inventory was full
 */
//TODO : FINISH ADD ITEM
bool Inventory::addItem(ItemStack itemStack) {
    inventory[0] = itemStack;
    return true;
}


void Inventory::clearInventory() {
    ItemStack emptyItemStack;

    for(int i = 0; i < size; i++) {
        inventory[i] = emptyItemStack;
    }
}

ItemStack *Inventory::getItem(unsigned short pos) {
    return &inventory[pos];
}
