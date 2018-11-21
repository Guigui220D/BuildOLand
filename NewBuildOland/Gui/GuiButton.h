
#pragma once


#include "Gui.h"

class GuiButton : public Gui {
public:
    GuiButton(StateBase* stateBase, std::string textString, sf::Vector2f pos);

    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;
    bool handleEvent(sf::Event e) override;

    bool onClick();

    inline void setSize(sf::Vector2f size) { background.setSize(size); }
    inline void setString(std::string str) { text.setString(str); }

private:
    sf::RectangleShape background;
    sf::Text text;

    bool hovered = false;
    bool clicked = false;

    bool clickDowned = false;

    sf::Vector2f pos;
};



