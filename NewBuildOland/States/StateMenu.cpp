#include <cmath>
#include "StateMenu.h"
#include "../Game.h"

StateMenu::StateMenu(Game &game) : StateBase(game)
{
    initAssets();

    //buttonLocal = ;


    GuiZone* center = new GuiZone(sf::FloatRect(.2f, .2f, .6f, .8f), 3.f / 4.f);
    center->setZoneWidth(110.f);
    center->guiElements.push_back(std::make_unique<MenuButton>(this, "Local", sf::Vector2f(5, 10)));
    center->guiElements.push_back(std::make_unique<MenuButton>(this, "Multiplayer", sf::Vector2f(5, 35)));
    center->guiElements.push_back(std::make_unique<TextInput>(this, sf::Vector2f(5, 65), "Username", 16, true));
    center->guiElements.push_back(std::make_unique<TextInput>(this, sf::Vector2f(5, 85), "Address", 0));
    guiDomain.zones.push_back(std::unique_ptr<GuiZone>(center));


    game.getWindow().setMouseCursorVisible(true);

    //Get background image
    backgroundRect.setTexture(assetManager.getTexture("TILESET"));
    backgroundRect.setTextureRect(sf::IntRect(69, 1, 32, 32));
    backgroundRect.setSize(sf::Vector2f(StateGame::TILE_SIZE, StateGame::TILE_SIZE));
    backgroundRect.setPosition(0, 0);

    //Get buildoland logo
    logoSprite.setTexture(*assetManager.getTexture("LOGO"));
    float logoWidth = logoSprite.getLocalBounds().width;
    float logoScale = 0.5;
    logoSprite.scale(logoScale, logoScale);
    logoSprite.setPosition(- logoWidth / 2 * logoScale, -game.getWorldView().getSize().y * 0.95f / 2);

    //Get sfml logo
    sfmlSprite.setScale(0.5f, 0.5f);
    sfmlSprite.setTexture(*assetManager.getTexture("SFML"));
    sfmlSprite.setPosition(-game.getWorldView().getSize().x / 2 * 0.97f,
                            game.getWorldView().getSize().y / 2 - sfmlSprite.getLocalBounds().height * 0.6f);
}

void StateMenu::initAssets()
{
    assetManager.loadFontFromFile("lucon.ttf", "LUCON");

    assetManager.loadTextureFromFile("inventorySelected.png", "SELECTED_SLOT");
    assetManager.loadTextureFromFile("inventoryBar.png", "INVENTORY_BAR");
    assetManager.loadTextureFromFile("newTileset.png", "TILESET");
    assetManager.loadTextureFromFile("logo.png", "LOGO");
    assetManager.loadTextureFromFile("sfml-logo-small.png", "SFML");
}

void StateMenu::handleInput() {
    Vector2i mousePos = sf::Mouse::getPosition(game->getWindow());
    /*
    //Handle onHover for the guiElements
    buttonMultiplayer->isHovered(mousePos);
    buttonLocal->isHovered(mousePos);
    nickInput->isHovered(mousePos);
    adressInput->isHovered(mousePos);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if(!isMouseLeftClicked) {
            //Just got clicked
            buttonMultiplayer->isActive(mousePos);
            buttonLocal->isActive(mousePos);
            nickInput->isActive(mousePos);
            adressInput->isActive(mousePos);
        }
        isMouseLeftClicked = true;

    } else {
        if(isMouseLeftClicked) {
            //Just released the click
            isMouseLeftClicked = false;

            //Send the event to the gui
            if(buttonLocal->isReleased(mousePos)) {
                //init the stategame as a local game
                game->setCurrentState(new StateGame(*game, false));
            }
            else if(buttonMultiplayer->isReleased(mousePos)) {
                //init the stategame as an online game
                game->setCurrentState(new StateGame(*game, true, nickInput->getInputText(), adressInput->getInputText()));
            }
        }
    }

*/
}

void StateMenu::update(float dt, bool focused) {
    guiDomain.update(dt);
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

    //And draw the gui
    guiDomain.draw(window);
}

void StateMenu::handleEvent(sf::Event &event)
{
    if (guiDomain.handleEvent(event))
        return;
    switch (event.type) {
        default:
            break;
    }
}
