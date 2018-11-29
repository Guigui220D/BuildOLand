#pragma once

#include "Gui.h"
#include "../Utils/Inventory.h"

class StateGame;

class InventoryMenuGui : public Gui
{
    public:
        InventoryMenuGui(StateGame *stateGame, sf::Vector2u size, Inventory* inv);

        void draw(sf::RenderWindow &window) override;
        void update(float dt) override;
        bool handleEvent(sf::Event e) override;


    protected:
        Inventory* inventory;

        sf::Texture background;
        sf::Sprite backgroundSprite;

    private:
};

