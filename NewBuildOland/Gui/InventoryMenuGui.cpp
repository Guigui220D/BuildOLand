#include "InventoryMenuGui.h"

#include "../States/StateGame.h"

#include <assert.h>

InventoryMenuGui::InventoryMenuGui(StateGame *stateGame, sf::Vector2u size, Inventory* inv) :
    Gui((StateBase*)stateGame),
    inventory(inv),
    size(size)
{
    assert(size.x > 0 && size.y > 0 && size.y <= 8 && size.x <= 8);
    assert(size.x * size.y <= inv->getSize());

    //Render background
    {
        sf::RenderTexture rd;
        rd.create(size.x * 40, size.y * 40);
        rd.clear(sf::Color(0, 0, 0, 127));

        sf::Sprite slot;
        slot.setTexture(*stateBase->getAssetManager()->getTexture("INVENTORY_SLOT"));

        sf::Image shade;
        shade.loadFromFile("Res/inventoryShade.png");

        for (unsigned int x = 0; x < size.x; x++)
        for (unsigned int y = 0; y < size.y; y++)
        {
            slot.setColor(shade.getPixel(x, y));
            slot.setPosition(sf::Vector2f(x * 40.f, y * 40.f));
            rd.draw(slot);
        }

        rd.display();
        background = rd.getTexture();
    }

    backgroundSprite.setTexture(background);

    selectedSprite.setTexture(*stateBase->getAssetManager()->getTexture("SELECTED_SLOT"));

    itemCountText.setFont(*stateGame->getAssetManager()->getFont("AKASHI"));
    itemCountText.setFillColor(sf::Color::White);
    itemCountText.setCharacterSize(10);
    itemCountText.setOutlineColor(sf::Color::Black);
    itemCountText.setOutlineThickness(1.f);

    updateContent();
}

void InventoryMenuGui::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
    window.draw(contentSprite);
    if (selected.x != -1)
        window.draw(selectedSprite);
}

void InventoryMenuGui::update(float dt)
{ }

bool InventoryMenuGui::handleEvent(sf::Event e)
{
    if (e.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos = stateBase->getGame()->getWindow().mapPixelToCoords(sf::Mouse::getPosition(stateBase->getGame()->getWindow()));
        if (backgroundSprite.getGlobalBounds().contains(mousePos))
        {
            sf::Vector2i slot(mousePos.x / 40.f, mousePos.y / 40.f);
            if (slot != selected)
            {
                if (selected.x != -1)
                {
                    //Swap items
                    ItemStack temp = inventory->getItem(selected.x + selected.y * size.x);
                    inventory->getItem(selected.x + selected.y * size.x) = inventory->getItem(slot.x + slot.y * size.x);
                    inventory->getItem(slot.x + slot.y * size.x) = temp;
                    updateContent();
                }
                else
                    selected = slot;
            }
            else
                selected = sf::Vector2i(-1, -1);
            selectedSprite.setPosition(sf::Vector2f(selected.x * 40.f, selected.y * 40.f));
            return true;
        }
    }
    return false;
}

void InventoryMenuGui::updateContent()
{
    //Render content
    {
        sf::RenderTexture rd;
        rd.create(size.x * 40, size.y * 40);
        rd.clear(sf::Color::Transparent);

        sf::Sprite itemSprite;
        itemSprite.setTexture(*GameGlobal::assets.getTexture("TILESET"));

        unsigned int i;
        for (unsigned int x = 0; x < size.x; x++)
        for (unsigned int y = 0; y < size.y; y++)
        {
            i = x + y * size.x;
            ItemStack itemStack = inventory->getItem(i);

            itemSprite.setTextureRect(itemStack.getItem()->getItemTextureRect());
            itemSprite.setPosition(sf::Vector2f(x * 40.f + 4.f, y * 40.f + 4.f));
            rd.draw(itemSprite);

            if (!itemStack.isEmpty())
            {
                itemCountText.setPosition(sf::Vector2f(x * 40.f + 6.f, y * 40.f + 23.f));
                itemCountText.setString(std::to_string(itemStack.getQuantity()));
                rd.draw(itemCountText);
            }
        }

        rd.display();
        content = rd.getTexture();
    }

    contentSprite.setTexture(content);
    selected = sf::Vector2i(-1, -1);
}
