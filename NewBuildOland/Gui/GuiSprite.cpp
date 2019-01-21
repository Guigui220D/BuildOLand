#include "GuiSprite.h"

GuiSprite::GuiSprite(StateBase* state, sf::Texture* texture, sf::Vector2f position, float scale, sf::Vector2f shadowPos) :
    Gui(state),
    sprite(*texture),
    shadow(shadowPos != sf::Vector2f()),
    shadowPos(shadowPos)
{
    sprite.setPosition(position);
    sprite.scale(sf::Vector2f(scale, scale));
}

void GuiSprite::draw(sf::RenderWindow &window)
{
    //Draw the shadow
    if (shadow)
    {
        sprite.setPosition(sprite.getPosition() + shadowPos);
        sprite.setColor(sf::Color::Black);
        window.draw(sprite);
    }
    //Draw the texture
    sprite.setPosition(sprite.getPosition() - shadowPos);
    sprite.setColor(sf::Color::White);
    window.draw(sprite);
}

void GuiSprite::update(float dt) { }
