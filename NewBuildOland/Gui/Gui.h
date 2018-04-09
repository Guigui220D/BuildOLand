#pragma once
#include <SFML/Graphics.hpp>

class StateGame;

class Gui : public sf::RectangleShape
{
    public:
        Gui(StateGame* game);
        virtual ~Gui();
        bool visible;
        virtual void drawMore(sf::RenderWindow &window);
        virtual void act();
    protected:
        StateGame* stateGame = nullptr;
    private:

};
