#pragma once


#include "../Placeables/Item.h"

class ItemStack {
public:
    ItemStack();
    ItemStack(Item* item);
    ItemStack(Item* item, unsigned short quantity);

    Item* getItem() const;
    unsigned short getQuantity() const;
    bool isEmpty();

    void setQuantity(unsigned short quantity);
    void setItem(Item *item);
    void add(unsigned int quantity = 1);
    void remove(unsigned int quantity = 1);

private:
    Item* item;
    unsigned short quantity;
};



