#pragma once
#include <SFML/Graphics.hpp>

class StateGame;

class Gui
{
public:
    Gui(StateGame* game);
    virtual ~Gui();

    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void update(float dt) = 0;

    virtual void eventResize();
protected:
    StateGame* stateGame = nullptr;
private:

};
