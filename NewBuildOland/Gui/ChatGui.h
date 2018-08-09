#pragma once


#include "Gui.h"
#include "TextInput.h"

class ChatGui : public Gui {

public:
    ChatGui(StateGame *stateGame);
    void draw(sf::RenderWindow &window) override;
    void update(float dt) override;
    void eventResize() override;

    bool isActive() const;
    void setIsActive(bool isActive);

    void eventInput(short unicode);

private:
    sf::Text text;
    sf::RectangleShape background;
    TextInput *textInput;

    bool active = false;
};



