#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Item {
public:
    Item(const std::string name);

    virtual bool isPlaceable() = 0;
    virtual bool isGround() = 0;

    inline std::string getName() const { return name; };

    virtual sf::IntRect getItemTextureRect() const;

    inline void setItemId(unsigned short id) { itemId = id; };
    inline unsigned short getItemId() const { return itemId; };

protected:
    std::string name;

    unsigned short itemId;
};



