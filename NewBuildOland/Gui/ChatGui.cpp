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

    addMessage(ChatMessage(" - Console Init - ", ChatColor::ChatGreen));
}

void ChatGui::draw(sf::RenderWindow &window)
{
    window.draw(background);
    float height = 0.f;
    unsigned int i = 0;
    bool remove = false;
    for (sf::Text msg : messages)
    {
        height += msg.getGlobalBounds().height + 2.f;
        if (160.f - height < -20.f)
        {
            remove = true;
            break;
        }
        msg.setPosition(sf::Vector2f(2.f, 160.f - height));
        window.draw(msg);
        i++;
    }
    if (remove)
        for (unsigned int j = 0; j < messages.size() - i; j++)
            messages.pop_back();
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
    //Create text
    sf::Text t;
    t.setFillColor(sf::Color((int)message.color));

    t.setOutlineThickness(2.f);
    t.setOutlineColor(sf::Color::Black);

    t.setCharacterSize(20.f);
    t.setScale(sf::Vector2f(.25f, .25f));

    t.setFont(*GameGlobal::assets.getFont("LUCON"));
    t.setString(message.content);

    //Add line returns to fit in chat window
    bool done = false;
    while (!done)
    {
        done = true;
        for (size_t i = 0; i < t.getString().getSize(); i++)
        {
            if (t.findCharacterPos(i).x > 95.f)
            {
                sf::String str = t.getString();
                str.insert(i - 1, '\n');
                t.setString(str);
                done = false;
                break;
            }
        }
    }

    messages.push_front(t);
}
