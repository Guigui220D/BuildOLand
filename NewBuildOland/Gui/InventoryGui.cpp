#include <sstream>
#include "InventoryGui.h"
#include "../States/StateGame.h"

InventoryGui::InventoryGui(StateGame *stateGame, Inventory *inventory, unsigned short *cursorId)
    : Gui(stateGame)
    , inventory(inventory)
    , cursorId(cursorId)
{
    //Load the inventory image
    if (!inventoryTexture.loadFromFile("Res/inventoryBar.png"))
        std::cout << "ERROR LOADING FROM 'Res/inventoryBar.png'" << std::endl;

    inventorySprite.setTexture(inventoryTexture);
    float inventoryWidth = inventorySprite.getLocalBounds().width;
    float inventoryHeight = inventorySprite.getLocalBounds().height;
    float inventoryMargin = 10.0f;
    inventorySprite.scale(inventoryScale, inventoryScale);
    inventorySprite.setPosition(-inventoryWidth / 2 * inventoryScale,
                                stateGame->getGuiView().getSize().y / 2 - inventoryHeight * inventoryScale - inventoryMargin);

    //Load the inventory selected cursor
    if (!selectedTexture.loadFromFile("Res/inventorySelected.png"))
        std::cout << "ERROR LOADING FROM 'Res/inventorySelected.png'" << std::endl;

    selectedSprite.setTexture(selectedTexture);
    selectedSprite.setScale(inventoryScale, inventoryScale);
    selectedSprite.setPosition(inventorySprite.getPosition().x + (*cursorId * 36) * inventoryScale,
                               inventorySprite.getPosition().y);


    //Load the item images
    for(unsigned i = 0; i < inventorySlots; i++){
        sf::Sprite* item = new Sprite();
        item->setScale(inventoryScale, inventoryScale);
        item->setPosition(inventorySprite.getPosition().x + 4 * inventoryScale + (i * 36) * inventoryScale ,
                          inventorySprite.getPosition().y + 4 * inventoryScale);
        itemSprites.push_back(item);
    }

    font.loadFromFile("Res/Font/lucon.ttf");
//    text.setFont(font);
//    text.setFillColor(sf::Color::Black);
//    text.setCharacterSize(16);
//    text.setScale(sf::Vector2f(0.002f, 0.002f));
//    text.setPosition(sf::Vector2f(0.3, 0.02));

    updateInventory();
}

void InventoryGui::update(float dt) {
    std::stringstream s;
    inventory->getItem(*cursorId)->getItem()->isGround();

    //Change the position of the cursor according to the cursorId
    selectedSprite.setPosition(inventorySprite.getPosition().x + (*cursorId * 36) * inventoryScale,
                               inventorySprite.getPosition().y);
}

void InventoryGui::draw(sf::RenderWindow &window) {
    //Draw the shadow of the inventory bar
    sf::Vector2f inventoryPos = inventorySprite.getPosition();
    inventorySprite.setColor(sf::Color(0, 0, 0, 100));
    inventorySprite.setPosition(inventoryPos.x + 5, inventoryPos.y + 5);
    window.draw(inventorySprite);
    //And the inventory
    inventorySprite.setColor(sf::Color(255, 255, 255, 255));
    inventorySprite.setPosition(inventoryPos.x, inventoryPos.y);
    window.draw(inventorySprite);

    //Draw all items of the bar
    for(int i = 0; i < inventorySlots; i++) {
        window.draw(*itemSprites[i]);
    }

    //Draw the selected cursor
    window.draw(selectedSprite);
}

void InventoryGui::updateInventory() {

    //Update the items of the inventory

    for(int i = 0; i < inventorySlots; i++) {
        Item *item = inventory->getItem(i)->getItem();
        sf::IntRect textureRect;

        //Get the item rect
        if(item->isPlaceable()) {
            if(item->isGround()) {
                textureRect = stateGame->getTileset()->getGroundByName(item->getName())->getTextureRect();
            } else {
                textureRect = stateGame->getTileset()->getBlockByName(item->getName())->getTextureRect();
            }

            itemSprites[i]->setTextureRect(textureRect);
            itemSprites[i]->setTexture(*stateGame->getTileset()->getTexture());
        } else {
            itemSprites[i]->setTextureRect(sf::IntRect(0, 0, 0, 0));
        }

    }
}

unsigned int InventoryGui::getInventorySlots() const {
    return inventorySlots;
}
