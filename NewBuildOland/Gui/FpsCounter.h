#pragma once
#include "Gui.h"

class FpsCounter : public Gui
{
    public:
        FpsCounter(StateGame* stateGame);
        virtual ~FpsCounter();

        void draw(sf::RenderWindow &window) override;
        void update(float dt) override;

        void eventResize() override;

protected:

    private:
        double getFPS();
        sf::Text text;
};

