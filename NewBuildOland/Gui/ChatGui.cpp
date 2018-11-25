#include "ChatGui.h"
#include "../States/StateGame.h"
#include "TextInput.h"

ChatGui::ChatGui(StateGame *stateGame) :
    Gui((StateBase*)stateGame)
{
    //Background
    background = sf::RectangleShape();
    background.setFillColor(sf::Color(0, 0, 0, 100));
    background.setSize(sf::Vector2f(100, 160));
}

void ChatGui::draw(sf::RenderWindow &window)
{
    window.draw(background);
    float height = 0.f;
    for (sf::Text msg : messages)
    {
        msg.setPosition(sf::Vector2f(0.f, height));
        window.draw(msg);
        height += msg.getGlobalBounds().height;
    }
}

void ChatGui::update(float dt)
{

}

bool ChatGui::handleEvent(sf::Event e)
{
    return false;
}

void ChatGui::addMessage(ChatMessage message)
{
    messages.push_back(message.getSfText());
}
