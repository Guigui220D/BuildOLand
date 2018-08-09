#include "ChatGui.h"
#include "../States/StateGame.h"
#include "TextInput.h"

ChatGui::ChatGui(StateGame *stateGame) : Gui(stateGame) {
    //Chatwidth = width from left to beggining of inventory (-10px)
    float chatwidth = stateGame->getGuiView().getSize().x / 2.0f - 292 - 10;

    text.setFont(*stateGame->getAssetManager()->getFont("lucon"));
    text.setFillColor(sf::Color::White);
    text.setString("Type your command here - Available soon");
    text.setPosition(-stateGame->getGuiView().getSize().x / 2.0f,
                     stateGame->getGuiView().getSize().y / 2.0f - text.getLocalBounds().height - 50);
    text.setCharacterSize(static_cast<unsigned int>(chatwidth * 1.0f / 23.1f));

    //BACKGROUND
    background = sf::RectangleShape();
    background.setFillColor(sf::Color(0, 0, 0, 100));


    background.setSize(sf::Vector2f(chatwidth, chatwidth * 0.5f));
    background.setPosition(-stateGame->getGuiView().getSize().x / 2.0f,
                           stateGame->getGuiView().getSize().y / 2.0f - background.getSize().y);

    //TEXT INPUT BAR
    //TODO: Make textInput a pure virtual class, so you can have more customisation
    //And also create a pure virtual setPosition method (so that you can calculate height / width etc)
    //Eventually a getHeight / getWidth method that you can set in the class, so it's easier to position it on the guiView
    textInput = new TextInput(stateGame, sf::Vector2f(-stateGame->getGuiView().getSize().x / 2.0f, 0), "Write here");
}

void ChatGui::draw(sf::RenderWindow &window) {

    //always shown
    window.draw(background);
    window.draw(text);

    //Only when user presses T or Enter
    if(active) {
        textInput->draw(window);
    }
}

void ChatGui::update(float dt) {
    textInput->update(dt);
}

void ChatGui::eventResize() {
    //Chatwidth = width from left to beggining of inventory (-10px)
    float chatwidth = stateGame->getGuiView().getSize().x / 2.0f - 292 - 10;

    //Position the text left of the screen
    text.setPosition(-stateGame->getGuiView().getSize().x / 2.0f,
                     stateGame->getGuiView().getSize().y / 2.0f - text.getLocalBounds().height - 50);
    text.setCharacterSize(static_cast<unsigned int>(chatwidth * 1.0f / 23.1f));

    background.setSize(sf::Vector2f(chatwidth, chatwidth * 0.5f));
    background.setPosition(-stateGame->getGuiView().getSize().x / 2.0f,
                           stateGame->getGuiView().getSize().y / 2.0f - background.getSize().y);
}

bool ChatGui::isActive() const {
    return active;
}

void ChatGui::setIsActive(bool isActive) {
    ChatGui::active = isActive;
}

void ChatGui::eventInput(short unicode) {
    textInput->eventInput(unicode);

}

