#include <cmath>
#include "StateMenu.h"
#include "../Game.h"

StateMenu::StateMenu(Game &game) : StateBase(game)
    , buttonLocal(this, "Local", sf::Vector2f(0, -100))
    , buttonMultiplayer(this, "Multiplayer", sf::Vector2f(0, 100))
    , nickInput(this, sf::Vector2f(0, 200), "Username", 16)
    , adressInput(this, sf::Vector2f(0, 300), "Address", 0)
{
    game.getWindow().setMouseCursorVisible(true);

    //Load background image
    if (!tilesetTexture.loadFromFile("Res/newTileset.png"))
    {
        std::cout << "ERROR LOADING FROM 'Res/newTileset.png'" << std::endl;
    }
    backgroundRect.setTexture(&tilesetTexture);
    backgroundRect.setTextureRect(sf::IntRect(69, 1, 32, 32));
    backgroundRect.setSize(sf::Vector2f(StateGame::TILE_SIZE, StateGame::TILE_SIZE));
    backgroundRect.setPosition(0, 0);

    //Loading buildoland logo
    if (!logo.loadFromFile("Res/logo.png"))
    {
        std::cout << "ERROR LOADING FROM 'Res/logo.png'" << std::endl;
    }
    logoSprite.setTexture(logo);
    float logoWidth = logoSprite.getLocalBounds().width;
    float logoScale = 0.5;
    logoSprite.scale(logoScale, logoScale);
    logoSprite.setPosition(- logoWidth / 2 * logoScale, -game.getWorldView().getSize().y * 0.95f / 2);

    //Loading sfml logo
    if (!sfmlLogo.loadFromFile("Res/sfml-logo-small.png"))
    {
        std::cout << "ERROR LOADING FROM 'Res/sfml-logo-small.png'" << std::endl;
    }
    sfmlSprite.setScale(0.5f, 0.5f);
    sfmlSprite.setTexture(sfmlLogo);
    sfmlSprite.setPosition(-game.getWorldView().getSize().x / 2 * 0.97f,
                            game.getWorldView().getSize().y / 2 - sfmlSprite.getLocalBounds().height * 0.6f);
}

void StateMenu::handleInput() {
    Vector2i mousePos = sf::Mouse::getPosition(game->getWindow());

    //Handle onHover for the guiElements
    buttonMultiplayer.isHovered(mousePos);
    buttonLocal.isHovered(mousePos);
    nickInput.isHovered(mousePos);
    adressInput.isHovered(mousePos);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(!isMouseLeftClicked) {
            //Just got clicked
            buttonMultiplayer.isActive(mousePos);
            buttonLocal.isActive(mousePos);
            nickInput.isActive(mousePos);
            adressInput.isActive(mousePos);
        }
        isMouseLeftClicked = true;

    } else {
        if(isMouseLeftClicked) {
            //Just released the click
            isMouseLeftClicked = false;

            //Send the event to the gui
            if(buttonLocal.isReleased(mousePos)) {
                //init the stategame as a local game
                game->setCurrentState(new StateGame(*game, false));
            }
            else if(buttonMultiplayer.isReleased(mousePos)) {
                //init the stategame as an online game
                game->setCurrentState(new StateGame(*game, true, nickInput.getInputText(), adressInput.getInputText()));
            }
        }
    }


}

void StateMenu::update(float dt, bool focused) {
    buttonLocal.update(dt);
    buttonMultiplayer.update(dt);
    nickInput.update(dt);
}

void StateMenu::draw(sf::RenderWindow &window) {
    window.setView(game->getWorldView());

    //======== BACKGROUND TILES ========//
    //Numbers of tiles you can fit into the width and height
    int rectNbX = ceil(window.getView().getSize().x / backgroundRect.getSize().x);
    int rectNbY = ceil(window.getView().getSize().y / backgroundRect.getSize().y);

    //Draw each tile
    float rectSize = backgroundRect.getSize().x;
    for(int x = -rectNbX / 2; x < rectNbX / 2 + 1; x++) {
        for(int y = -rectNbY / 2; y < rectNbY / 2 + 2; y++) {

            //From the center as origin, we draw in the x and y axis the grass texture.
            backgroundRect.setPosition(-rectSize / 2.0f - x * rectSize, -rectSize / 2.0f - y * rectSize);
            window.draw(backgroundRect);
        }
    }

    //============= LOGO =============//
    //Draw the logo shadow
    sf::Vector2f logoPos = logoSprite.getPosition();
    logoSprite.setColor(sf::Color(0, 0, 0, 100));
    logoSprite.setPosition(logoPos.x + 5, logoPos.y + 5);
    window.draw(logoSprite);
    //And the real logo
    logoSprite.setColor(sf::Color(255, 255, 255, 255));
    logoSprite.setPosition(logoPos.x, logoPos.y);
    window.draw(logoSprite);

    //============= SFML =============//
    window.draw(sfmlSprite);

    //And draw the button
    buttonLocal.draw(window);
    buttonMultiplayer.draw(window);
    nickInput.draw(window);
    adressInput.draw(window);


}

void StateMenu::handleEvent(sf::Event &event) {
    switch (event.type) {
        //RESIZE EVENT
        case sf::Event::Resized:
            //Send the event to all gui elements
            buttonMultiplayer.eventResize();
            buttonLocal.eventResize();
            nickInput.eventResize();
            adressInput.eventResize();
            //Reposition sfml logo
            sfmlSprite.setPosition(-game->getWorldView().getSize().x / 2 * 0.97f,
                                   game->getWorldView().getSize().y / 2 - sfmlSprite.getLocalBounds().height * 0.6f);
            break;
        case sf::Event::TextEntered:
            nickInput.eventInput(event.text.unicode);
            adressInput.eventInput(event.text.unicode);
            break;
    }

}
