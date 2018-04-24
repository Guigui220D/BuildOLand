#pragma once
#include "Gui.h"

class FpsCounter : public Gui
{
    public:
        FpsCounter(StateGame* game);
        virtual ~FpsCounter();
        void drawMore(sf::RenderWindow &window) override;
        void act() override;
    protected:

    private:
        double getFPS();
        sf::Font font;
        sf::Text text;
};

