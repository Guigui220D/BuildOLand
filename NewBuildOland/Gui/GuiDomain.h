#pragma once
#include "GuiLayer.h"

class GuiDomain
{
    public:
        GuiDomain();

        bool handleEvent(sf::Event e);
        void draw(sf::RenderWindow& rw);
        std::vector<std::unique_ptr<GuiLayer>> layers;

    protected:

    private:
};
