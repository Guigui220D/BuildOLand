#pragma once
#include "GuiZone.h"

class GuiDomain
{
    public:
        GuiDomain();

        //Dispatch an event to all zones
        bool handleEvent(sf::Event e, sf::RenderWindow& rw);
        void draw(sf::RenderWindow& rw);
        void update(float dt, sf::RenderWindow& rw);

        inline void setEnabled(bool enable) { enabled = enable; }
        inline bool isEnabled() const { return enabled; }

        //The zones in the domain
        std::vector<std::unique_ptr<GuiZone>> zones;

    private:
        bool enabled;
};
