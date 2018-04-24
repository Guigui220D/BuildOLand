
#pragma once


#include "Item.h"

class ItemAir : public Item {
public:
    ItemAir();

    bool isPlaceable() override;

    bool isGround() override;
};



