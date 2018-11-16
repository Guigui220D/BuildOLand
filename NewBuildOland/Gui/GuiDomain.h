#pragma once
#include "GuiZone.h"

class GuiDomain
{
    public:
        GuiDomain();

        //Dispatch an event to all zones
        bool handleEvent(sf::Event e);
        void draw(sf::RenderWindow& rw);
        void update(float dt);
        //The zones in the domain
        std::vector<std::unique_ptr<GuiZone>> zones;

    private:
};
