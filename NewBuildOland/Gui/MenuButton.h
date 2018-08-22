
#pragma once


#include "Gui.h"

class StateMenu;

class MenuButton : public Gui {
public:
    MenuButton(StateMenu* stateMenu,std::string textString, sf::Vector2f pos);

    void update(float dt) override;

    void draw(sf::RenderWindow &window) override;

    bool isReleased(sf::Vector2i mousePos) override;
    bool isHovered(sf::Vector2i mousePos) override;
    bool isActive(sf::Vector2i mousePos) override;

    void eventResize() override;

private:
    StateMenu* stateMenu;

    sf::RectangleShape background;
    sf::Text text;

    sf::Vector2f pos;

    bool hovered = false;
    bool active = false;
    bool released = false;

    bool justGotResized = false;
};



