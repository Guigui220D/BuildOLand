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

    sf::Text t;
    t.setString(" - Console Init - ");
    t.setOutlineColor(sf::Color::Black);
    t.setOutlineThickness(2.f);
    t.setFillColor(sf::Color::Green/*((int)color)*/);
    t.setCharacterSize(20.f);
    t.setFont(*GameGlobal::assets.getFont("LUCON"));
    t.setScale(sf::Vector2f(.25f, .25f));
    messages.push_back(t);
}

void ChatGui::draw(sf::RenderWindow &window)
{
    window.draw(background);
    float height = 0.f;
    unsigned int i = 0;
    bool remove = false;
    for (sf::Text msg : messages)
    {
        if (160.f - height < -20.f)
        {
            remove = true;
            break;
        }
        msg.setPosition(sf::Vector2f(2.f, 152.f - height));
        window.draw(msg);
        height += msg.getGlobalBounds().height + 2.f;
        i++;
    }
    if (remove)
        for (unsigned int j = 0; j < messages.size() - i; j++)
        {
            messages.pop_back();
            printf("Remove message\n");
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
    sf::Text t;
    t.setString(message.content);
    t.setOutlineColor(sf::Color::Black);
    t.setOutlineThickness(2.f);
    t.setFillColor(sf::Color((int)message.color));
    t.setCharacterSize(20.f);
    t.setScale(sf::Vector2f(.25f, .25f));
    t.setFont(*GameGlobal::assets.getFont("LUCON"));
    messages.push_front(t);
}
