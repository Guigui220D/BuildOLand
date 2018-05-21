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

    //Load the font in order to show the quantity of the items
    if (!font.loadFromFile("Res/Font/Akashi.ttf"))
        std::cout << "ERROR LOADING FROM 'Res/Font/Akashi.ttf'" << std::endl;

    //Load the item images
    for(unsigned i = 0; i < inventorySlots; i++){
        //Place the sprite correctly
        sf::Sprite* item = new Sprite();
        item->setScale(inventoryScale, inventoryScale);
        item->setPosition(inventorySprite.getPosition().x + 4 * inventoryScale + (i * 36) * inventoryScale ,
                          inventorySprite.getPosition().y + 4 * inventoryScale);
        itemSprites.push_back(item);

        //And place the text correctly
        sf::Text* text = new Text();
        text->setFont(font);
        text->setFillColor(sf::Color::White);
        text->setCharacterSize(8 * inventoryScale);
        //No need for setting the position now, as we need to change it according to the length of the text
        itemTexts.push_back(text);
    }


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

    for(int i = 0; i < inventorySlots; i++) {
        ItemStack *itemStack = inventory->getItem(i);
        Item *item = itemStack->getItem();
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

        //Set the quantity of the item
        itemTexts[i]->setString(std::to_string(itemStack->getQuantity()));
        itemTexts[i]->setPosition(inventorySprite.getPosition().x + 34 * inventoryScale + (i * 36) * inventoryScale - itemTexts[i]->getLocalBounds().width,
                                  inventorySprite.getPosition().y + 26 * inventoryScale);


    }
}

unsigned int InventoryGui::getInventorySlots() const {
    return inventorySlots;
}
