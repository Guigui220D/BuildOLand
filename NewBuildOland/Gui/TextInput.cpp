#include "TextInput.h"
#include "../States/StateBase.h"
#include "../Game.h"

TextInput::TextInput(StateBase *stateBase, sf::Vector2f pos, std::string placeHolder, unsigned maxSize, bool alphaNumeric) : Gui(nullptr)
    , stateBase(stateBase)
    , pos(pos)
    , inputText(placeHolder)
    , maxSize(maxSize)
{
    alphaNumericOnly = alphaNumeric;

    //BACKGROUND
    background = sf::RectangleShape();
    background.setFillColor(sf::Color(0, 0, 0, 100));
    background.setSize(sf::Vector2f(100.f, 20.f));
    background.setPosition(pos.x, pos.y);


    //TEXT
    text.setFont(*GameGlobal::assets.getFont("LUCON"));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(40);
    text.setScale(sf::Vector2f(.3f, .3f));
    text.setString(placeHolder);
    text.setPosition(pos.x + 5.f, pos.y + 2.5f);

    //CURSOR ( | )
    cursor = sf::RectangleShape();
    cursor.setFillColor(sf::Color::White);
    cursor.setSize(sf::Vector2f(1, 13));
    cursor.setPosition(pos.x + text.getGlobalBounds().width + 6.5f, pos.y + 2.5f);


}

void TextInput::update(float dt) {
    cursorTime += dt;
    //Reset after 2 secs
    cursorTime = cursorTime > 1.06f ? 0 : cursorTime;
}

void TextInput::draw(sf::RenderWindow &window) {
    window.draw(background);
    window.draw(text);
    if(active && cursorTime <= 0.53f) {
        window.draw(cursor);
    }
}

bool TextInput::handleEvent(sf::Event e) {
    if (e.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos = stateBase->getGame()->getWindow().mapPixelToCoords(sf::Mouse::getPosition(stateBase->getGame()->getWindow()));
        active = background.getGlobalBounds().contains(mousePos);
    }
    if (e.type == sf::Event::TextEntered && active)
    {
        eventInput(e.text.unicode);
        return true;
    }
    if (active && e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Return)
    {
        enterPressed = true;
        active = false;
        return true;
    }
    return false;
}

void TextInput::eventInput(short unicode) {
    if(active) {
        //First time typing something
        if(isPlaceHolder) {
            isPlaceHolder = false;
            inputText = "";
        }
        //Erase key
        if(unicode == 8) {
            if(inputText.length() >= 1) {
                inputText = inputText.substr(0, inputText.length() - 1);
            }
        } else if(maxSize == 0 || inputText.length() < maxSize){
            if (!alphaNumericOnly
                || unicode == 45 || unicode == 95     //- and _
                || (unicode >= 97 && unicode <= 122)  //letters
                || (unicode >= 65 && unicode <= 90)   //LETTERS
                || (unicode >= 48 && unicode <= 57))
            {
                std::string input = unicodeConvert.to_bytes(unicode);
                inputText += input;
            }
        }

        text.setString(inputText);
        cursor.setPosition(pos.x + text.getGlobalBounds().width + 6.5f, pos.y + 2.5f);
    }
}

const std::string &TextInput::getInputText() const {
    return inputText;
}

bool TextInput::onEnter()
{
    if (!enterPressed)
        return false;
    enterPressed = false;
    return true;
}
