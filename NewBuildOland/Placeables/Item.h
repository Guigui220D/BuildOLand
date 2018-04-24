#pragma once
#include <iostream>

class Item {
public:
    Item(const std::string name);

    virtual bool isPlaceable() = 0;
    virtual bool isGround() = 0;

    std::string getName();

protected:
    std::string name;
};



