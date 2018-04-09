#pragma once
#include <Gui.h>

class FpsCounter : public Gui
{
    public:
        FpsCounter(StateGame* game);
        virtual ~FpsCounter();
        virtual void drawMore(sf::RenderWindow &window);
        void act() override;
    protected:

    private:
        double getFPS();
};

