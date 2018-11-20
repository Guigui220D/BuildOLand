#pragma once
#include "GuiZone.h"

class GuiShroud : public GuiZone
{
    public:
        GuiShroud(sf::Color color = sf::Color(0, 0, 0, 128));
        void setColor(sf::Color col);

        bool handleEvent(sf::Event e, sf::RenderWindow& rw) override;
        void draw(sf::RenderWindow& rw) override;
        void update(float dt, sf::RenderWindow& rw) override;
    private:
        sf::RectangleShape shroud;

};
