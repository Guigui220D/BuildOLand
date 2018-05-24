#include "StateMenu.h"
#include "../Game.h"

StateMenu::StateMenu(Game &game) : StateBase(game) {

    //Load background image
    if (!backgroundImage.loadFromFile("Res/menubackground.jpg"))
    {
        std::cout << "ERROR LOADING FROM 'Res/menubackground.jpg'" << std::endl;
    }
    backgroundSprite.setTexture(backgroundImage);
    float backgroundWidth = backgroundSprite.getLocalBounds().width;
    float backgroundHeight = backgroundSprite.getLocalBounds().height;
    float backgroundScale = 0.7;
    backgroundSprite.scale(backgroundScale, backgroundScale);
    backgroundSprite.setPosition(- backgroundWidth / 2 * backgroundScale, - backgroundHeight / 2 * backgroundScale);

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


    //Load text
    font.loadFromFile("Res/Font/lucon.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(35);
    text.setString("Press <SPACE> to start the game !");
    text.setPosition(-text.getLocalBounds().width / 2, 0);
}

void StateMenu::handleInput() {
    if(sf::Keyboard::isKeyPressed(Keyboard::Space) && !isSpacePressed) {

        //Init the state game
        game->setCurrentState(new StateGame(*game, true));
        isSpacePressed = true;
    } else if(!sf::Keyboard::isKeyPressed(Keyboard::Space)){
        isSpacePressed = false;
    }
}

void StateMenu::update(float dt) {
    elapsedTime+= dt;
    if(elapsedTime > 2.0f) {
        elapsedTime = 0.0f;
        text.setString("Press <SPACE> to start the game !");
        text.setPosition(-text.getLocalBounds().width / 2, 0);
    } else if(elapsedTime > 1.0f) {
        text.setString(" > Press <SPACE> to start the game ! <");
        text.setPosition(-text.getLocalBounds().width / 2 - 4.5f, 0);
    }
}

void StateMenu::draw(sf::RenderWindow &window) {
    window.setView(game->getWorldView());

    window.draw(backgroundSprite);

    //Draw the logo shadow
    sf::Vector2f logoPos = logoSprite.getPosition();
    logoSprite.setColor(sf::Color(0, 0, 0, 100));
    logoSprite.setPosition(logoPos.x + 5, logoPos.y + 5);
    window.draw(logoSprite);
    //And the real logo
    logoSprite.setColor(sf::Color(255, 255, 255, 255));
    logoSprite.setPosition(logoPos.x, logoPos.y);
    window.draw(logoSprite);

    window.draw(text);
}
