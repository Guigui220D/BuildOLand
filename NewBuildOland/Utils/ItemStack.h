#pragma once

#include "../Placeables/Item.h"

class ItemSet;

class ItemStack {
public:
    static ItemSet* currentItemSet;

    ItemStack();
    ItemStack(Item* item, unsigned short count);

    Item* getItem() const;
    inline unsigned short getID() const { return id; };
    inline unsigned short getQuantity() const { return quantity; };
    inline bool isEmpty() { return quantity == 0 || id == 0; };

    inline void add(unsigned short count = 1) { quantity += count; };
    void remove(unsigned short count = 1);
    bool stack(ItemStack otherStack);

    inline int getValue() const { return value; };

private:
    //Item* item;
    union
    {
        struct
        {
            unsigned short id;
            unsigned short quantity;
        };
        int value;
    };
};



