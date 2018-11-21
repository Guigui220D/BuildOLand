
#pragma once


#include "StateBase.h"

class GuiButton;
class TextInput;

class StateMenu : public StateBase {

public:
    StateMenu(Game &game);

    void initAssets() override;

    void handleInput()                  override;
    void update(float dt, bool focused) override;
    void draw(sf::RenderWindow &window) override;

    void handleEvent(sf::Event &event)  override;

private:
    sf::RectangleShape backgroundRect;

    sf::Sprite logoSprite;
    sf::Sprite sfmlSprite;

    GuiDomain guiDomain;
    GuiButton* buttonLocal;
    GuiButton* buttonMultiplayer;
    TextInput* nicknameInput;
    TextInput* addressInput;

    sf::Texture woodenBackGround;

    float elapsedTime = 0;

    bool isSpacePressed = false;
    bool isMouseLeftClicked = false;
};



