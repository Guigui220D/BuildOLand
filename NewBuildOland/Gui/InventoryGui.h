
#pragma once


#include <vector>
#include "Gui.h"
#include "../Utils/Inventory.h"

class InventoryGui : public Gui {
public:
    InventoryGui(StateGame *stateGame, Inventory *inventory, unsigned short *cursorId);

    void draw(sf::RenderWindow &window) override;

    void update(float dt) override;

    void updateInventory();

    unsigned int getInventorySlots() const;

private:
    float inventoryScale = 2;
    unsigned int inventorySlots = 8;

    sf::Texture inventoryTexture;
    sf::Sprite inventorySprite;

    sf::Texture selectedTexture;
    sf::Sprite selectedSprite;


    std::vector<sf::Sprite*> itemSprites;

    sf::Font font;
//    sf::Text text;
    Inventory *inventory;
    unsigned short *cursorId;
};



