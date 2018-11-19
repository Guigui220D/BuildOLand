
#pragma once


#include "Gui.h"

class StateMenu;

class MenuButton : public Gui {
public:
    MenuButton(StateMenu* stateMenu, std::string textString, sf::Vector2f pos);

    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    bool handleEvent(sf::Event e) override;

    bool onClick();

private:
    StateMenu* stateMenu;

    sf::RectangleShape background;
    sf::Text text;

    bool hovered = false;
    bool clicked = false;

    sf::Vector2f pos;
};



