
#pragma once


#include <codecvt>
#include "Gui.h"
#include "../States/StateBase.h"

class StateMenu;

class TextInput : public Gui{

public:
    TextInput(StateBase *stateBase, sf::Vector2f pos, std::string placeHolder, unsigned maxSize = 0);

    void update(float dt) override;

    void draw(sf::RenderWindow &window) override;

    bool isActive(sf::Vector2i mousePos) override;

    void eventResize() override;

    void eventInput(short unicode);

    const std::string &getInputText() const;

private:
    StateBase* stateBase;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>,wchar_t> unicodeConvert;

    const float margin = 15.0f;
    sf::Vector2f pos;
    float cursorTime = 0.0f;
    std::string inputText;
    bool isPlaceHolder = true;
    unsigned maxSize;

    sf::RectangleShape background;
    sf::RectangleShape cursor;
    sf::Text text;

    bool active = false;
    bool wasActive = false;
};



