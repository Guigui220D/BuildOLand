#include "ItemStack.h"
#include "Inventory.h"
#include "../Placeables/ItemAir.h"

ItemStack::ItemStack() {
    item = new ItemAir();
    ItemStack::quantity = 0;
}

ItemStack::ItemStack(Item* item) {
    ItemStack::item = item;
    ItemStack::quantity = 1;
}

ItemStack::ItemStack(Item* item, unsigned short quantity) {
    ItemStack::item = item;
    ItemStack::quantity = quantity;
}

unsigned short ItemStack::getQuantity() const {
    return quantity;
}

Item* ItemStack::getItem() const {
    return item;
}

void ItemStack::setQuantity(unsigned short quantity) {
    ItemStack::quantity = quantity;
}

bool ItemStack::isEmpty() {
    return quantity <= 0;
}

void ItemStack::setItem(Item *item) {
    ItemStack::item = item;
}

void ItemStack::add(unsigned int quantity) {
    ItemStack::quantity+= quantity;
}

void ItemStack::remove(unsigned int quantity) {
    ItemStack::quantity -= quantity;

    if(quantity < 0) {
        ItemStack::quantity = 0;
    }
}
