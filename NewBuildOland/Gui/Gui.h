#pragma once
#include <SFML/Graphics.hpp>

class StateBase;

class Gui
{
public:
    Gui(StateBase* stateBase);
    virtual ~Gui();

    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void update(float dt) = 0;

    virtual bool handleEvent(sf::Event e);

protected:
    StateBase* stateBase = nullptr;
private:

};
