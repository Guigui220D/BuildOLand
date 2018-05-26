
#pragma once


#include "StateBase.h"
#include "../Gui/MenuButton.h"

class StateMenu : public StateBase {

public:
    StateMenu(Game &game);

    void handleInput() override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;

    void handleEvent(sf::Event &event) override;

private:
    sf::Texture tilesetTexture;
    sf::RectangleShape backgroundRect;

    sf::Texture logo;
    sf::Texture sfmlLogo;
    sf::Sprite logoSprite;
    sf::Sprite sfmlSprite;

    MenuButton buttonLocal;
    MenuButton buttonMultiplayer;

    float elapsedTime = 0;

    bool isSpacePressed = false;
    bool isMouseLeftClicked = false;
};



