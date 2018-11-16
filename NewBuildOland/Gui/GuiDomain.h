#pragma once
#include "GuiZone.h"

class GuiDomain
{
    public:
        GuiDomain();

        //Dispatch an event to all zones
        bool handleEvent(sf::Event e);
        //Ask all the zones to draw their GUIs
        void draw(sf::RenderWindow& rw);
        //The zones in the domain
        std::vector<std::unique_ptr<GuiZone>> zones;

    private:
};
