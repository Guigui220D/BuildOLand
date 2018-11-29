#include <sstream>
#include "InventoryGui.h"
#include "../States/StateGame.h"

InventoryGui::InventoryGui(StateGame *stateGame, Inventory *inventory, unsigned short *cursorId) :
    Gui(stateGame),
    stateGame(stateGame),
    inventory(inventory),
    cursorId(cursorId)
{
    //Get the inventory image
    inventorySprite.setTexture(*stateGame->getAssetManager()->getTexture("INVENTORY_BAR"));

    //Get the inventory selected cursor
    selectedSprite.setTexture(*stateGame->getAssetManager()->getTexture("SELECTED_SLOT"));
    selectedSprite.setPosition(*cursorId * 36, 0);

    //Load the item images
    for(unsigned i = 0; i < inventorySlots; i++){
        //Place the sprite correctly
        sf::Sprite* item = new Sprite();
        item->setPosition(i * 36 + 4, 4);
        itemSprites.push_back(item);

        //And place the text correctly
        sf::Text* text = new Text();
        text->setFont(*stateGame->getAssetManager()->getFont("AKASHI"));
        text->setFillColor(sf::Color::White);
        text->setCharacterSize(8);
        //No need for setting the position now, as we need to change it according to the length of the text
        itemTexts.push_back(text);

        itemSprites[i]->setTexture(*GameGlobal::assets.getTexture("TILESET"));
    }


    updateInventory();
}

void InventoryGui::update(float dt) {
    std::stringstream s;
    inventory->getItem(*cursorId).getItem()->isGround();

    //Change the position of the cursor according to the cursorId
    selectedSprite.setPosition(inventorySprite.getPosition().x + (*cursorId * 36),
                               inventorySprite.getPosition().y);
}

void InventoryGui::draw(sf::RenderWindow &window) {
    //Draw the shadow of the inventory bar
    inventorySprite.setColor(sf::Color(0, 0, 0, 100));
    inventorySprite.setPosition(5, 5);
    window.draw(inventorySprite);
    //And the inventory
    inventorySprite.setColor(sf::Color(255, 255, 255));
    inventorySprite.setPosition(0, 0);
    window.draw(inventorySprite);

    //Draw all items of the bar
    for(unsigned int i = 0; i < inventorySlots; i++) {
        //Draw the sprites
        window.draw(*itemSprites[i]);

        //And draw the text shadow
        sf::Vector2f textPos = itemTexts[i]->getPosition();
        itemTexts[i]->setFillColor(sf::Color(0, 0, 0, 100));
        itemTexts[i]->setPosition(textPos.x + 2, textPos.y + 2);
        window.draw(*itemTexts[i]);
        //And draw the real text
        itemTexts[i]->setFillColor(sf::Color(255, 255, 255, 255));
        itemTexts[i]->setPosition(textPos.x, textPos.y);
        window.draw(*itemTexts[i]);
    }
    //Draw the selected cursor
    window.draw(selectedSprite);
}

void InventoryGui::updateInventory() {

    //Update the items of the inventory
    for(unsigned int i = 0; i < inventorySlots; i++) {
        ItemStack itemStack = inventory->getItem(i);

        //Get the item rect
        itemSprites[i]->setTextureRect(itemStack.getItem()->getItemTextureRect());

        //Set the quantity of the item
        itemTexts[i]->setString(std::to_string(itemStack.getQuantity()));
        itemTexts[i]->setPosition(34 + (i * 36) - itemTexts[i]->getLocalBounds().width, 26);
    }
}

unsigned int InventoryGui::getInventorySlots() const {
    return inventorySlots;
}
