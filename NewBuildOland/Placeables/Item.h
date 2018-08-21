#pragma once
#include <iostream>

class Item {
public:
    Item(const std::string name);

    virtual bool isPlaceable() = 0;
    virtual bool isGround() = 0;

    inline std::string getName() { return name; };

protected:
    std::string name;
};



