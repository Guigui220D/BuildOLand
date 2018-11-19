#include <cmath>
#include "StateMenu.h"
#include "../Game.h"

#include "../Gui/MenuButton.h"
#include "../Gui/TextInput.h"
#include "../Gui/GuiSprite.h"

StateMenu::StateMenu(Game &game) : StateBase(game)
{
    initAssets();

    //Create the zone for the interface
    GuiZone* center = new GuiZone(sf::FloatRect(.2f, .3f, .6f, .7f), 3.f / 4.f);
    center->setZoneWidth(110.f);
    center->guiElements.push_back(std::make_unique<MenuButton>(this, "Local", sf::Vector2f(5, 0)));
    //Beurk
    buttonLocal = (MenuButton*)center->guiElements.back().get();
    center->guiElements.push_back(std::make_unique<MenuButton>(this, "Multiplayer", sf::Vector2f(5, 25)));
    buttonMultiplayer = (MenuButton*)center->guiElements.back().get();
    center->guiElements.push_back(std::make_unique<TextInput>(this, sf::Vector2f(5, 55), "Username", 16, true));
    nicknameInput = (TextInput*)center->guiElements.back().get();
    center->guiElements.push_back(std::make_unique<TextInput>(this, sf::Vector2f(5, 75), "Address", 0));
    addressInput = (TextInput*)center->guiElements.back().get();
    guiDomain.zones.push_back(std::unique_ptr<GuiZone>(center));    //Add the zone to the domain

    //Title
    GuiZone* title = new GuiZone(sf::FloatRect(.1f, .05f, .8f, .20f), 1626.f / 195.f);
    title->setZoneWidth(1626.f);
    title->guiElements.push_back(std::make_unique<GuiSprite>(this, assetManager.getTexture("LOGO")));
    guiDomain.zones.push_back(std::unique_ptr<GuiZone>(title));
    //SFML
    GuiZone* sfml = new GuiZone(sf::FloatRect(.05f, .8f, .15f, .15f), 373.f / 113., ZoneHAlign::HLeft, ZoneVAlign::VBottom);
    sfml->setZoneWidth(373.f);
    sfml->guiElements.push_back(std::make_unique<GuiSprite>(this, assetManager.getTexture("SFML")));
    guiDomain.zones.push_back(std::unique_ptr<GuiZone>(sfml));

    game.getWindow().setMouseCursorVisible(true);

    //Get background image
    backgroundRect.setTexture(assetManager.getTexture("TILESET"));
    backgroundRect.setTextureRect(sf::IntRect(69, 1, 32, 32));
    backgroundRect.setSize(sf::Vector2f(StateGame::TILE_SIZE, StateGame::TILE_SIZE));
    backgroundRect.setPosition(0, 0);
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

void StateMenu::handleInput()
{
    if (buttonLocal->onClick())
        game->setCurrentState(new StateGame(*game, false));
    if (buttonMultiplayer->onClick())
        std::cout << "Multiplayer mode is still in development in this version\n" << nicknameInput->getInputText() << "\n" << addressInput->getInputText() << "\n";
        //game->setCurrentState(new StateGame(*game, true, nicknameInput->getInputText(), addressInput->getInputText()));
}

void StateMenu::update(float dt, bool focused)
{
    guiDomain.update(dt, game->getWindow());
}

void StateMenu::draw(sf::RenderWindow &window)
{
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

    //Draw the gui
    guiDomain.draw(window);
}

void StateMenu::handleEvent(sf::Event &event)
{
    if (guiDomain.handleEvent(event, game->getWindow()))
        return;
}
