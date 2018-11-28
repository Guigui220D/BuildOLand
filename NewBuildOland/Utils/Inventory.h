#pragma once

#include <vector>
#include "ItemStack.h"

class Inventory {
public:
    Inventory(unsigned short size);
    ~Inventory();

    bool addItem(ItemStack itemStack);
    void clearInventory();

    ItemStack& getItem(unsigned short pos);

    unsigned short getSize() const;

private:
    ItemStack* inventory;
    unsigned short size;
};



