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
bool Inventory::addItem(ItemStack itemStack) {
    std::string itemName = itemStack.getItem()->getName();

    //First search if there is anything you can stack
    for(unsigned short i = 0; i < inventory.size(); i++) {
        if(inventory[i].getItem() == itemStack.getItem()) {
            inventory[i].add(itemStack.getQuantity());
            return true;
        }
    }

    //Otherwise search for air
    for(unsigned short i = 0; i < inventory.size(); i++) {
        if(inventory[i].getItem()->getName() == "AIR") {
            inventory[i] = itemStack;
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

ItemStack *Inventory::getItem(unsigned short pos) {
    return &inventory[pos];
}
