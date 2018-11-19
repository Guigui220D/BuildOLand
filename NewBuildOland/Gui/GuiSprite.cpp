#include "GuiSprite.h"

GuiSprite::GuiSprite(StateBase* state, sf::Texture* texture, sf::Vector2f position) :
    Gui(state),
    sprite(*texture)
{
    sprite.setPosition(position);
}

void GuiSprite::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void GuiSprite::update(float dt) { }
