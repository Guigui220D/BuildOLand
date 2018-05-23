
#pragma once


#include "StateBase.h"
#include "../Gui/MenuButton.h"

class StateMenu : public StateBase {

public:
    StateMenu(Game &game);

    void handleInput() override;
    void update(float dt) override;
    void draw(sf::RenderWindow &window) override;

private:
    sf::Texture tilesetTexture;
    sf::RectangleShape backgroundRect;

    sf::Texture logo;
    sf::Sprite logoSprite;

    MenuButton buttonLocal;
    MenuButton buttonMultiplayer;

    float elapsedTime = 0;

    bool isSpacePressed = false;
    bool isMouseLeftClicked = false;
};



