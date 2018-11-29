#include "InventoryMenuGui.h"

#include "../States/StateGame.h"

#include <assert.h>
#include <iostream>

InventoryMenuGui::InventoryMenuGui(StateGame *stateGame, sf::Vector2u size, Inventory* inv) :
    Gui((StateBase*)stateGame),
    inventory(inv)
{
    assert(size.x > 0 && size.y > 0 && size.y <= 8 && size.x <= 8);
    assert(size.x * size.y <= inv->getSize());

    //Render background
    {
        sf::RenderTexture rd;
        rd.create(size.x * 40, size.y * 40);
        rd.clear(sf::Color::Transparent);

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
}

void InventoryMenuGui::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
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
            sf::Vector2u slot(mousePos.x / 40.f, mousePos.y / 40.f);
            std::cout << "Inventry clicked (slot " << slot.x << ", " << slot.y << ")\n";
            return true;
        }
    }
    return false;
}
