
#pragma once


#include "StateBase.h"

class StateMenu : public StateBase {

public:
    StateMenu(Game &game);

    void handleInput() override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;

private:
    sf::Texture backgroundImage;
    sf::Sprite backgroundSprite;

    sf::Texture logo;
    sf::Sprite logoSprite;

    sf::Font font;
    sf::Text text;

    bool isSpacePressed = false;
};



