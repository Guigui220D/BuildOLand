#include "ChatGui.h"
#include "../States/StateGame.h"
#include "TextInput.h"

ChatGui::ChatGui(StateGame *stateGame) :
    Gui((StateBase*)stateGame),
    sentMessage("")
{
    //Background
    background = sf::RectangleShape();
    background.setFillColor(sf::Color(0, 0, 0, 100));
    background.setSize(sf::Vector2f(100, 160));

    inputText.setFont(*GameGlobal::assets.getFont("LUCON"));
    inputText.setFillColor(sf::Color::Cyan);
    inputText.setOutlineColor(sf::Color::Black);
    inputText.setOutlineThickness(2.f);
    inputText.setCharacterSize(20.f);
    inputText.setScale(sf::Vector2f(.25f, .25f));
    inputText.setString("> |");

    addMessage(ChatMessage(" - Console Init - ", ChatColor::ChatGreen));
}

void ChatGui::draw(sf::RenderWindow &window)
{
    window.draw(background);
    float height = 0.f;
    unsigned int i = 0;
    bool remove = false;

    //Input text
    height += inputText.getGlobalBounds().height + 2.f;
    inputText.setPosition(sf::Vector2f(2.f, 160.f - height));
    window.draw(inputText);

    height += 5.f;

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
    if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::T)
    {
        lock = false;
    }
    if (e.type == sf::Event::TextEntered)
    {
        eventInput(e.text.unicode);
        return true;
    }
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Return)
    {
        if (input.length() == 0)
            return false;
        enterPressed = true;
        addMessage(ChatMessage(input, ChatColor::ChatRed));
        sentMessage = input;
        inputText.setString("> |"); input = ""; displayInput = "";
        return true;
    }
    return false;
}

void ChatGui::eventInput(short unicode)
{
    if (lock)
        return;
    //Erase key
    if(unicode == 8 && input.length() > 0)
    {
        if (displayInput[displayInput.length() - 1] == '\n')
            displayInput = displayInput.substr(0, displayInput.length() - 1);
        input = input.substr(0, input.length() - 1);
        displayInput = displayInput.substr(0, displayInput.length() - 1);
    }
    else if (unicode >= 32 && input.length() < 255) //Chars below 32 are control chars
    {
        std::string inputt = unicodeConvert.to_bytes(unicode);
        input += inputt;
        displayInput += inputt;
    }

    inputText.setString("> " + displayInput + "|");
    //Add line returns to fit in chat window
    if (inputText.getGlobalBounds().width > 100.f)
    {
        displayInput.insert(displayInput.length() - 1, "\n");
        inputText.setString("> " + displayInput + "|");
    }
}

const std::string &ChatGui::getInputText() const {
    return input;
}

const std::string &ChatGui::getLastMessage() const {
    return sentMessage;
}

bool ChatGui::onEnter()
{
    if (!enterPressed)
        return false;
    enterPressed = false;
    return true;
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
