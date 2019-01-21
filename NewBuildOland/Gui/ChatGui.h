#pragma once

#include "Gui.h"
#include "TextInput.h"
#include "ChatMessage.h"

#include <deque>

class StateGame;

class ChatGui : public Gui {

public:
    ChatGui(StateGame *stateGame);

    void draw(sf::RenderWindow &window) override;
    void update(float dt) override;
    bool handleEvent(sf::Event e) override;

    void addMessage(ChatMessage message);

    const std::string &getInputText() const;
    const std::string &getLastMessage() const;
    inline void clearInput()
    { inputText.setString("> |"); input = ""; displayInput = ""; lock = true; }

    bool onEnter();

private:
    sf::RectangleShape background;

    std::deque<sf::Text> messages;

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> unicodeConvert;
    sf::Text inputText;
    std::string input;
    std::string displayInput;
    std::string sentMessage;
    void eventInput(short unicode);

    bool enterPressed;

    bool lock = false;
};

