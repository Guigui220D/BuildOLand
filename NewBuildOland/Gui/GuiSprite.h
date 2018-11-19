#pragma once
#include "Gui.h"

class GuiSprite : public Gui
{
    public:
        GuiSprite(StateBase* state, sf::Texture* texture, sf::Vector2f position = sf::Vector2f());

        void update(float dt) override;
        void draw(sf::RenderWindow &window) override;

    protected:
        sf::Sprite sprite;
};
