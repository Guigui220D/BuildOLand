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

private:
    sf::RectangleShape background;

    std::deque<sf::Text> messages;
};

