
#pragma once


#include "Gui.h"
#include "../Utils/Inventory.h"

class InventoryGui : public Gui {
public:
    InventoryGui(StateGame *game, Inventory *inventory, unsigned short *cursorId);

    void drawMore(sf::RenderWindow &window) override;

    void act() override;
private:
    sf::Font font;
    sf::Text text;
    Inventory *inventory;
    unsigned short *cursorId;
};



