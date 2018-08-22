
#pragma once


#include "StateBase.h"
#include "../Gui/MenuButton.h"
#include "../Gui/TextInput.h"

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

    std::unique_ptr<MenuButton> buttonLocal;
    std::unique_ptr<MenuButton> buttonMultiplayer;
    std::unique_ptr<TextInput> nickInput;
    std::unique_ptr<TextInput> adressInput;

    float elapsedTime = 0;

    bool isSpacePressed = false;
    bool isMouseLeftClicked = false;
};



