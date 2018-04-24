#pragma once

#include <vector>
#include "ItemStack.h"

class Inventory {
public:
    Inventory(unsigned short size);

    void setItem(unsigned short pos, ItemStack itemStack);
    bool addItem(ItemStack itemStack);
    void clearInventory();

    ItemStack* getItem(unsigned short pos);

private:
    std::vector<ItemStack> inventory;
    unsigned short size;
};



