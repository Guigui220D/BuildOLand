#pragma once
#include <SFML/Graphics.hpp>

class StateGame;

class Gui
{
public:
    Gui(StateGame* stateGame);
    virtual ~Gui();

    virtual void draw(sf::RenderWindow &window) = 0;
    virtual void update(float dt) = 0;

    virtual bool handleEvent(sf::Event e);

    virtual bool isReleased(sf::Vector2i mousePos);
    virtual bool isActive(sf::Vector2i mousePos);
    virtual bool isHovered(sf::Vector2i mousePos);
protected:
    StateGame* stateGame = nullptr;
private:

};
