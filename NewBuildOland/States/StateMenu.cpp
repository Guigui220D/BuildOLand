#include <cmath>
#include "StateMenu.h"
#include "../Game.h"

#include "../Gui/GuiButton.h"
#include "../Gui/TextInput.h"
#include "../Gui/GuiSprite.h"

#include "../Gui/GuiShroud.h"

StateMenu::StateMenu(Game &game) : StateBase(game)
{
    initAssets();

    //Render wooden background
    {
        sf::RenderTexture rd;
        rd.create(330, 440);
        rd.clear(sf::Color::Transparent);

        sf::Sprite a, b;
        a.setTexture(*GameGlobal::assets.getTexture("TILESET"));
        a.setTextureRect(sf::IntRect(69, 35, 32, 32));
        //a.setColor(sf::Color(190, 190, 190));
        b.setTexture(*GameGlobal::assets.getTexture("TILESET"));
        b.setTextureRect(sf::IntRect(69, 69, 32, 29));
        a.setScale(sf::Vector2f(3.438f, 3.438f / 1.5f)); //Totally arbitrary numbers
        b.setScale(sf::Vector2f(3.438f, 3.794f));       //Do not touch

        for (int i = 0; i < 3; i++)
        {
            a.setPosition(sf::Vector2f(i * 110.f, 0));
            rd.draw(a);
            for (int j = 0; j < 10; j++)
            {
                b.setPosition(sf::Vector2f(i * 110.f, j * 110.f + 110.f / 1.5f));
                rd.draw(b);
            }
        }


        rd.display();
        woodenBackGround = rd.getTexture();
    }

    //Create the zone for the interface
    GuiZone* center = new GuiZone(sf::FloatRect(.2f, .3f, .6f, .7f), 3.f / 4.f, ZoneHAlign::HCenter, ZoneVAlign::VTop);
    center->setZoneWidth(110.f);
    center->guiElements.push_back(std::make_unique<GuiSprite>(this, &woodenBackGround, sf::Vector2f(), 1.f / 3.f));
    center->guiElements.push_back(std::make_unique<GuiButton>(this, "Local", sf::Vector2f(5, 30)));
    buttonLocal = (GuiButton*)center->guiElements.back().get();
    center->guiElements.push_back(std::make_unique<GuiButton>(this, "Multiplayer", sf::Vector2f(5, 55)));
    buttonMultiplayer = (GuiButton*)center->guiElements.back().get();
    center->guiElements.push_back(std::make_unique<TextInput>(this, sf::Vector2f(5, 85), "Username", 16, true));
    nicknameInput = (TextInput*)center->guiElements.back().get();
    center->guiElements.push_back(std::make_unique<TextInput>(this, sf::Vector2f(5, 105), "Address", 0));
    addressInput = (TextInput*)center->guiElements.back().get();
    guiDomain.zones.push_back(std::unique_ptr<GuiZone>(center));    //Add the zone to the domain

    //Title
    GuiZone* title = new GuiZone(sf::FloatRect(.1f, .05f, .8f, .20f), 1626.f / 195.f);
    title->setZoneWidth(1700.f);
    title->guiElements.push_back(std::make_unique<GuiSprite>(this, GameGlobal::assets.getTexture("LOGO"), sf::Vector2f(), 1.f, sf::Vector2f(10.f, 10.f)));
    guiDomain.zones.push_back(std::unique_ptr<GuiZone>(title));

    //SFML
    GuiZone* sfml = new GuiZone(sf::FloatRect(.05f, .8f, .15f, .15f), 373.f / 113., ZoneHAlign::HLeft, ZoneVAlign::VBottom);
    sfml->setZoneWidth(400.f);
    sfml->guiElements.push_back(std::make_unique<GuiSprite>(this, assetManager.getTexture("SFML"), sf::Vector2f(), 1.f, sf::Vector2f(5.f, 5.f)));
    guiDomain.zones.push_back(std::unique_ptr<GuiZone>(sfml));

    game.getWindow().setMouseCursorVisible(true);

    //Get background image
    backgroundRect.setTexture(GameGlobal::assets.getTexture("TILESET"));
    backgroundRect.setTextureRect(sf::IntRect(69, 1, 32, 32));
    backgroundRect.setSize(sf::Vector2f(StateGame::TILE_SIZE, StateGame::TILE_SIZE));
    backgroundRect.setPosition(0, 0);
}

void StateMenu::initAssets()
{
    assetManager.loadFontFromFile("lucon.ttf", "LUCON");

    assetManager.loadTextureFromFile("inventorySelected.png", "SELECTED_SLOT");
    assetManager.loadTextureFromFile("inventoryBar.png", "INVENTORY_BAR");
    assetManager.loadTextureFromFile("sfml-logo-small.png", "SFML");
}

void StateMenu::handleInput()
{
    if (nicknameInput->onEnter())
        addressInput->setActive(true);
    if (addressInput->onEnter())
    {
        if (nicknameInput->isStillPlaceHolder() || addressInput->isStillPlaceHolder())
        {
            nicknameInput->setActive(true);
        }
        else
            std::cout << "Multiplayer mode is still in development in this version\n" << nicknameInput->getInputText() << "\n" << addressInput->getInputText() << "\n";
    }
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
